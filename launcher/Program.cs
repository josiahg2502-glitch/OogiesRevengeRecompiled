namespace OogiesRevenge;

static class Program
{
    [STAThread]
    static int Main(string[] args)
    {
        // Headless: "--extract <image> <outdir>" writes <outdir>\extract.log; exit 0 ok, 3 wrong disc, 1 error.
        if (args.Length == 3 && args[0] == "--extract")
        {
            var log = new List<string>();
            try
            {
                using var disc = XboxDisc.Open(args[1]);
                log.Add($"partition at {disc.PartitionOffset:X} problem=\"{disc.Problem()}\"");
                if (disc.Problem().Length > 0) { Write(args[2], log); return 3; }
                int n = disc.Extract(args[2], (done, total, name) => { if (done % 100 == 0) log.Add($"{done}/{total} {name}"); });
                log.Add($"extracted {n} files");
                Write(args[2], log);
                return 0;
            }
            catch (Exception e)
            {
                log.Add("ERROR " + e);
                Write(args[2], log);
                return 1;
            }
        }
        if (args.Length == 0 && MainForm.StartGameIfReady()) return 0;
        ApplicationConfiguration.Initialize();
        // "--shots <dir>": draw every page to <dir>\<page>.png and exit. "--selftest": build every page, then exit 0.
        int shots = Array.IndexOf(args, "--shots");
        var form = new MainForm(shots >= 0 && shots + 1 < args.Length ? args[shots + 1] : null);
        if (args.Contains("--selftest")) { form.Shown += (_, _) => form.Close(); }
        Application.Run(form);
        return 0;
    }

    static void Write(string dir, List<string> log)
    {
        Directory.CreateDirectory(dir);
        File.WriteAllLines(Path.Combine(dir, "extract.log"), log);
    }
}
