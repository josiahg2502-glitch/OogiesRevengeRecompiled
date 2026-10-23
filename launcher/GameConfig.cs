namespace OogiesRevenge;

// UserData\Config.toml, edited line by line, inside the key's section, comments and unknown keys kept (the game
// reads it at start, xboxrecomp/runtime/config.cpp). shortcut: '#' inside a quoted value counts as a comment start;
// no key the launcher writes holds one.
sealed class GameConfig
{
    readonly string path;
    readonly List<string> lines;

    public GameConfig(string path)
    {
        this.path = path;
        lines = File.Exists(path) ? File.ReadAllLines(path).ToList() : new List<string>();
    }

    static string Strip(string line)
    {
        int i = line.IndexOf('#');
        return (i >= 0 ? line[..i] : line).Trim();
    }

    (int start, int end) Section(string section)
    {
        int s = lines.FindIndex(l => Strip(l) == "[" + section + "]");
        if (s < 0) return (-1, -1);
        int e = lines.FindIndex(s + 1, l => Strip(l).StartsWith('['));
        return (s, e < 0 ? lines.Count : e);
    }

    int KeyLine(string section, string key)
    {
        var (s, e) = Section(section);
        for (int i = s + 1; s >= 0 && i < e; i++)
        {
            string t = Strip(lines[i]);
            if (t.StartsWith(key) && t[key.Length..].TrimStart().StartsWith('=')) return i;
        }
        return -1;
    }

    // The raw value with surrounding quotes removed, or null when the key is absent.
    public string? Get(string section, string key)
    {
        int i = KeyLine(section, key);
        if (i < 0) return null;
        string v = Strip(lines[i]);
        v = v[(v.IndexOf('=') + 1)..].Trim();
        return v.Length >= 2 && (v[0] == '"' || v[0] == '\'') && v[^1] == v[0] ? v[1..^1] : v;
    }

    public void Set(string section, string key, string raw)
    {
        string line = key + " = " + raw;
        int i = KeyLine(section, key);
        if (i >= 0) { lines[i] = line; return; }
        var (s, e) = Section(section);
        if (s < 0)
        {
            if (lines.Count > 0 && lines[^1].Length > 0) lines.Add("");
            lines.Add("[" + section + "]");
            lines.Add(line);
            return;
        }
        while (e > s + 1 && lines[e - 1].Trim().Length == 0) e--;
        lines.Insert(e, line);
    }

    public void Remove(string section, string key)
    {
        int i = KeyLine(section, key);
        if (i >= 0) lines.RemoveAt(i);
    }

    // TOML basic string; the values the launcher writes (paths, key names) hold no quotes or backslashes to escape
    // except Windows paths, which use the literal form.
    public void SetString(string section, string key, string value) =>
        Set(section, key, value.Contains('\\') ? "'" + value.Replace("'", "") + "'" : "\"" + value.Replace("\"", "") + "\"");

    public void Save()
    {
        Directory.CreateDirectory(Path.GetDirectoryName(path)!);
        File.WriteAllLines(path, lines);
    }
}
