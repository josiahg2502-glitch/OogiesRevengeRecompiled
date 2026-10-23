using System.Security.Cryptography;
using System.Text;

namespace OogiesRevenge;

// An Xbox disc image (Redump .iso of XGD1/2/3, or a plain xiso): the game partition's XDVDFS file system.
// The image is untrusted input: names are checked before any file is written, sizes against the image.
sealed class XboxDisc : IDisposable
{
    const int Sector = 2048;
    static readonly byte[] Magic = Encoding.ASCII.GetBytes("MICROSOFT*XBOX*MEDIA");
    static readonly long[] Partitions = { 0x18300000, 0xFD90000, 0x2080000, 0 };  // XGD1, XGD2, XGD3, xiso

    // The executable this port was recompiled from: Tim Burton's The Nightmare Before Christmas: Oogie's Revenge,
    // USA (title 42560004, version 1). Only its exact bytes run.
    public const string WantedXbeSha256 = "9a8319c7b1cb5ee29781bf641a0cf549c221fdc57effb8f72085608019f41548";

    readonly FileStream file;
    public long PartitionOffset { get; }
    readonly List<Entry> files = new();

    public record Entry(string Path, long Offset, long Length);

    XboxDisc(FileStream file, long partition)
    {
        this.file = file;
        PartitionOffset = partition;
        var head = Read(partition + 32L * Sector + 20, 8);
        uint rootSector = BitConverter.ToUInt32(head, 0), rootSize = BitConverter.ToUInt32(head, 4);
        Walk(rootSector, rootSize, "", new HashSet<(uint, uint)>(), 0);
    }

    public static XboxDisc Open(string path)
    {
        var f = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read, 1 << 20);
        foreach (var p in Partitions)
        {
            if (p + 33L * Sector > f.Length) continue;
            f.Position = p + 32L * Sector;
            var m = new byte[Magic.Length];
            f.ReadExactly(m);
            if (m.AsSpan().SequenceEqual(Magic)) return new XboxDisc(f, p);
        }
        f.Dispose();
        throw new InvalidDataException("this is not an Xbox disc image (no Xbox file system found)");
    }

    byte[] Read(long at, int count)
    {
        if (at < 0 || at + count > file.Length) throw new InvalidDataException("the image is cut short (a damaged or incomplete dump)");
        file.Position = at;
        var b = new byte[count];
        file.ReadExactly(b);
        return b;
    }

    // A directory is a binary tree of entries: left/right subtree offsets (in dwords), sector, size, attributes, name.
    void Walk(uint sector, uint size, string prefix, HashSet<(uint, uint)> seen, int depth)
    {
        if (depth > 32 || size == 0 || size > 64 << 20 || !seen.Add((sector, size))) return;
        var table = Read(PartitionOffset + (long)sector * Sector, (int)size);
        var stack = new Stack<int>();
        stack.Push(0);
        int guard = 0;
        while (stack.Count > 0 && guard++ < 100000)
        {
            int off = stack.Pop();
            if (off + 14 > table.Length || (table[off] == 0xFF && table[off + 1] == 0xFF)) continue;
            ushort left = BitConverter.ToUInt16(table, off), right = BitConverter.ToUInt16(table, off + 2);
            uint start = BitConverter.ToUInt32(table, off + 4), length = BitConverter.ToUInt32(table, off + 8);
            byte attr = table[off + 12], nameLen = table[off + 13];
            if (off + 14 + nameLen > table.Length) continue;
            string name = Encoding.Latin1.GetString(table, off + 14, nameLen);
            if (name.Length == 0 || name == "." || name == ".." || name.IndexOfAny(Path.GetInvalidFileNameChars()) >= 0)
                throw new InvalidDataException($"the image holds an unsafe file name: {name}");
            if (left != 0) stack.Push(left * 4);
            if (right != 0) stack.Push(right * 4);
            string path = prefix.Length == 0 ? name : prefix + "\\" + name;
            if ((attr & 0x10) != 0) Walk(start, length, path, seen, depth + 1);
            else files.Add(new Entry(path, PartitionOffset + (long)start * Sector, length));
        }
    }

    public IReadOnlyList<Entry> Files => files;

    // Empty when this is the right game, else a sentence for the player.
    public string Problem()
    {
        var xbe = files.FirstOrDefault(e => e.Path.Equals("default.xbe", StringComparison.OrdinalIgnoreCase));
        if (xbe == null) return "This Xbox disc has no game executable (default.xbe).";
        if (xbe.Length > 64 << 20) return "This disc's game executable is not the expected one.";
        var bytes = Read(xbe.Offset, (int)xbe.Length);
        return Convert.ToHexString(SHA256.HashData(bytes)).Equals(WantedXbeSha256, StringComparison.OrdinalIgnoreCase)
            ? ""
            : "This is not The Nightmare Before Christmas: Oogie's Revenge for the Xbox (USA). " +
              "Only that version runs, because the port was built from its exact game code.";
    }

    // Copies every file into outDir; progress(done, total, name) after each file. Returns the number of files.
    public int Extract(string outDir, Action<int, int, string> progress)
    {
        var root = Path.GetFullPath(outDir);
        Directory.CreateDirectory(root);
        var buffer = new byte[4 << 20];
        int done = 0;
        foreach (var e in files)
        {
            var target = Path.GetFullPath(Path.Combine(root, e.Path));
            if (!target.StartsWith(root + Path.DirectorySeparatorChar, StringComparison.OrdinalIgnoreCase))
                throw new InvalidDataException("the image tried to write outside the game folder");
            if (e.Offset + e.Length > file.Length) throw new InvalidDataException("the image is cut short (a damaged or incomplete dump)");
            Directory.CreateDirectory(Path.GetDirectoryName(target)!);
            using (var o = new FileStream(target, FileMode.Create, FileAccess.Write, FileShare.None, 1 << 20))
            {
                file.Position = e.Offset;
                long left = e.Length;
                while (left > 0)
                {
                    int n = file.Read(buffer, 0, (int)Math.Min(left, buffer.Length));
                    if (n <= 0) throw new InvalidDataException("the image is cut short (a damaged or incomplete dump)");
                    o.Write(buffer, 0, n);
                    left -= n;
                }
            }
            progress(++done, files.Count, e.Path);
        }
        return done;
    }

    public void Dispose() => file.Dispose();
}
