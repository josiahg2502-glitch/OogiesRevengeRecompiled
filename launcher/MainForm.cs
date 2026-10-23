using System.Diagnostics;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;

namespace OogiesRevenge;

// The launcher window: a Halloween Town night under the title, a jack-o'-lantern under the menu, and one card per
// page (Play, Display, Controls, Mods). Everything it changes goes to UserData\Config.toml, which the game reads at
// start. All art is drawn here; nothing from the game is shipped.
sealed class MainForm : Form
{
    const string GameExe = "OogiesRevenge.exe", AppTitle = "The Nightmare Before Christmas: Oogie's Revenge";
    static Color Hex(string s) => ColorTranslator.FromHtml(s);
    // Halloween Town at night: purple-black sky, the moon, pumpkin orange, Oogie's sackcloth green.
    static readonly Color Cream = Hex("#ECE6DA"), Paper = Hex("#FBF8F1"), Ink = Hex("#1A1424"), Purple = Hex("#4B2A7B"),
        PurpleLight = Hex("#E7DDF3"), Pumpkin = Hex("#EE7A1E"), Gold = Hex("#F7C04E"), Oogie = Hex("#7E9E4A"),
        NightTop = Hex("#120E1F"), NightLow = Hex("#3A2858"), Moon = Hex("#F3EDD3"), Good = Hex("#2F7D4F"), Warn = Hex("#B4561A");

    // Fonts are in points and grow with Windows display scaling; every pixel size goes through S() so it grows too.
    static float k = 1f;
    static int S(int v) => (int)Math.Round(v * k);
    static Size S(int w, int h) => new(S(w), S(h));
    static Padding S(int l, int t, int r, int b) => new(S(l), S(t), S(r), S(b));

    readonly string gameDir, exePath, userData, configPath, modsDir, discDir;
    readonly string? shotDir;
    readonly Panel content = new() { Dock = DockStyle.Fill };
    readonly List<(Button button, Control page)> pages = new();
    Label playStatus = null!, dumpHelp = null!;
    Button chooseDisc = null!, playButton = null!;
    ProgressBar progress = null!;

    public MainForm(string? shotDir = null)
    {
        this.shotDir = shotDir;
        k = DeviceDpi / 96f;
        (gameDir, exePath) = FindGame();
        userData = Path.Combine(gameDir, "UserData");
        configPath = Path.Combine(userData, "Config.toml");
        modsDir = Path.Combine(userData, "mods");
        discDir = Path.Combine(gameDir, "Disc", "files");

        Text = AppTitle;
        try { Icon = Icon.ExtractAssociatedIcon(Environment.ProcessPath!); } catch { }
        var area = Screen.PrimaryScreen?.WorkingArea.Size ?? new Size(S(1060), S(740));
        ClientSize = new Size(Math.Min(S(1060), area.Width - 40), Math.Min(S(740), area.Height - 60));
        MinimumSize = new Size(Math.Min(S(900), area.Width), Math.Min(S(620), area.Height));
        BackColor = Cream;
        Font = new Font("Segoe UI", 10.5f);
        StartPosition = FormStartPosition.CenterScreen;
        DoubleBuffered = true;
        content.Padding = S(16, 12, 20, 16);

        var header = new BufferedPanel { Dock = DockStyle.Top, Height = S(170) };
        header.Paint += PaintHeader;
        var nav = new BufferedFlow { Dock = DockStyle.Left, Width = S(220), FlowDirection = FlowDirection.TopDown, Padding = S(16, 18, 0, 0), WrapContents = false, BackColor = Hex("#211A30") };
        nav.Paint += PaintNav;
        var frame = new System.Windows.Forms.Timer { Interval = 50 };
        frame.Tick += (_, _) =>
        {
            if (!animate || WindowState == FormWindowState.Minimized) return;
            nav.Invalidate(new Rectangle(0, navArtTop, nav.Width, Math.Max(0, nav.Height - navArtTop)));
            float glow = (float)(Math.Sin(T * 3) + 1) / 2;  // PLAY breathes between pumpkin and gold
            if (playButton.Enabled) playButton.BackColor = Color.FromArgb(Lerp(Pumpkin.R, Gold.R, glow), Lerp(Pumpkin.G, Gold.G, glow), Lerp(Pumpkin.B, Gold.B, glow));
        };
        frame.Start();
        Controls.Add(content);
        Controls.Add(nav);
        Controls.Add(header);

        AddPage(nav, "Play", BuildPlayPage());
        AddPage(nav, "Display", BuildDisplayPage());
        AddPage(nav, "Controls", BuildControlsPage());
        AddPage(nav, "Mods", BuildModsPage());
        ShowPage(pages[0].button);
        Shown += (_, _) =>
        {
            if (shotDir == null) return;
            // Headless visual check: every page drawn to <dir>\<page>.png.
            Directory.CreateDirectory(shotDir);
            shotShift = 9;
            foreach (var p in pages)
            {
                ShowPage(p.button);
                Application.DoEvents();
                using var bmp = new Bitmap(Width, Height);
                DrawToBitmap(bmp, new Rectangle(Point.Empty, Size));
                bmp.Save(Path.Combine(shotDir, p.button.Text + ".png"));
            }
            Close();
        };
    }

    // The game folder: data\ beside the launcher (release), or the source tree root with build\OogiesRevenge.exe (dev).
    // The game has its own menu (Settings, Controls, Mods): once a disc is set up, opening the launcher starts the game
    // there straight away. The launcher's own window is for setting a disc up (or "--setup").
    public static bool StartGameIfReady()
    {
        var (dir, exe) = FindGame();
        var xbe = Path.Combine(dir, "Disc", "files", "default.xbe");
        try
        {
            if (!File.Exists(exe) || !File.Exists(xbe)) return false;
            using var f = File.OpenRead(xbe);
            if (!Convert.ToHexString(System.Security.Cryptography.SHA256.HashData(f)).Equals(XboxDisc.WantedXbeSha256, StringComparison.OrdinalIgnoreCase))
                return false;
            Process.Start(new ProcessStartInfo(exe) { WorkingDirectory = dir, UseShellExecute = true });
            return true;
        }
        catch (Exception) { return false; }
    }

    static (string gameDir, string exe) FindGame()
    {
        for (var d = new DirectoryInfo(AppContext.BaseDirectory); d != null; d = d.Parent)
        {
            var release = Path.Combine(d.FullName, "data", GameExe);
            if (File.Exists(release)) return (Path.Combine(d.FullName, "data"), release);
            var dev = Path.Combine(d.FullName, "build", GameExe);
            if (File.Exists(dev) && File.Exists(Path.Combine(d.FullName, "CMakeLists.txt"))) return (d.FullName, dev);
        }
        var data = Path.Combine(AppContext.BaseDirectory, "data");
        return (data, Path.Combine(data, GameExe));
    }

    void AddPage(FlowLayoutPanel nav, string title, Control page)
    {
        var button = new Button
        {
            Text = title, Size = S(188, 50), FlatStyle = FlatStyle.Flat, BackColor = Paper, ForeColor = Ink,
            Font = new Font("Segoe UI", 13f, FontStyle.Bold), TextAlign = ContentAlignment.MiddleLeft, Padding = S(12, 0, 0, 0),
            Margin = S(0, 0, 0, 10), Cursor = Cursors.Hand,
        };
        button.FlatAppearance.BorderColor = Ink;
        button.FlatAppearance.BorderSize = S(2);
        button.Click += (_, _) => ShowPage(button);
        button.MouseEnter += (_, _) => { if (button.BackColor == Paper) button.BackColor = PurpleLight; };
        button.MouseLeave += (_, _) => { if (button.BackColor == PurpleLight) button.BackColor = Paper; };
        page.Dock = DockStyle.Fill;
        page.Visible = false;
        content.Controls.Add(page);
        nav.Controls.Add(button);
        pages.Add((button, page));
    }

    void ShowPage(Button button)
    {
        foreach (var (b, page) in pages)
        {
            bool on = b == button;
            b.BackColor = on ? Purple : Paper;
            b.ForeColor = on ? Color.White : Ink;
            page.Visible = on;
        }
        RefreshDisc();
    }

    // ----- The art: header and side column, drawn -----
    readonly bool animate = SystemInformation.UIEffectsEnabled;
    readonly Stopwatch clock = Stopwatch.StartNew();
    double T => (animate ? clock.Elapsed.TotalSeconds : 1.0) + shotShift;
    double shotShift;
    Bitmap? headerImage;
    int navArtTop;

    static int Lerp(int a, int b, float f) => (int)(a + (b - a) * f);

    static FontFamily TitleFont()
    {
        foreach (var name in new[] { "Chiller", "Papyrus", "Segoe UI Black" })
            if (FontFamily.Families.Any(f => f.Name == name)) return new FontFamily(name);
        return new FontFamily("Segoe UI");
    }

    // Halloween Town at night: the sky, stars, the full moon behind Spiral Hill's curl, a crooked fence, and the title.
    void BuildHeader(Size size)
    {
        headerImage?.Dispose();
        headerImage = new Bitmap(size.Width, size.Height);
        using var g = Graphics.FromImage(headerImage);
        g.SmoothingMode = SmoothingMode.AntiAlias;
        g.PixelOffsetMode = PixelOffsetMode.HighQuality;
        float W = size.Width, H = size.Height;
        using (var sky = new LinearGradientBrush(new RectangleF(0, 0, W, H), NightTop, NightLow, LinearGradientMode.Vertical)) g.FillRectangle(sky, 0, 0, W, H);
        var rng = new Random(13);
        for (int i = 0; i < 70; i++)
        {
            float x = (float)rng.NextDouble() * W, y = (float)rng.NextDouble() * H * 0.7f, r = S(1) * (0.5f + (float)rng.NextDouble());
            using var star = new SolidBrush(Color.FromArgb(90 + rng.Next(140), Moon));
            g.FillEllipse(star, x, y, r * 2, r * 2);
        }
        // the moon with a soft glow
        float mr = H * 0.62f, mx = W * 0.78f, my = H * 0.42f;
        for (int i = 6; i >= 1; i--)
        {
            using var glow = new SolidBrush(Color.FromArgb(12, Moon));
            float gr = mr * (1 + i * 0.09f);
            g.FillEllipse(glow, mx - gr, my - gr, gr * 2, gr * 2);
        }
        using (var moon = new SolidBrush(Moon)) g.FillEllipse(moon, mx - mr, my - mr, mr * 2, mr * 2);
        using (var crater = new SolidBrush(Color.FromArgb(40, Hex("#B9AF8E"))))
        {
            g.FillEllipse(crater, mx - mr * 0.45f, my - mr * 0.30f, mr * 0.34f, mr * 0.28f);
            g.FillEllipse(crater, mx + mr * 0.15f, my + mr * 0.12f, mr * 0.26f, mr * 0.22f);
        }
        // Spiral Hill: a black hill whose tip curls into a spiral in front of the moon
        using (var hill = new GraphicsPath())
        {
            float baseY = H + S(4), hx = mx - mr * 0.2f;
            hill.AddBezier(W * 0.42f, baseY, W * 0.55f, H * 0.80f, hx - mr * 0.15f, H * 0.62f, hx, H * 0.48f);
            hill.AddBezier(hx, H * 0.48f, hx + mr * 0.05f, H * 0.38f, hx + mr * 0.30f, H * 0.36f, hx + mr * 0.32f, H * 0.46f);
            hill.AddBezier(hx + mr * 0.32f, H * 0.46f, hx + mr * 0.34f, H * 0.56f, hx + mr * 0.12f, H * 0.58f, hx + mr * 0.10f, H * 0.50f);
            hill.AddBezier(hx + mr * 0.10f, H * 0.50f, hx + mr * 0.08f, H * 0.62f, hx + mr * 0.25f, H * 0.80f, W * 0.98f, baseY);
            hill.CloseFigure();
            using var black = new SolidBrush(Hex("#07050B"));
            g.FillPath(black, hill);
        }
        // a crooked graveyard fence along the bottom
        using (var fence = new Pen(Hex("#07050B"), S(3)))
            for (float x = W * 0.38f; x < W; x += S(14))
            {
                float tilt = (float)Math.Sin(x * 0.37) * S(4), top = H - S(26) - (float)Math.Abs(Math.Sin(x * 0.11)) * S(10);
                g.DrawLine(fence, x, H, x + tilt, top);
                g.DrawLine(fence, x + tilt, top, x + tilt + S(3), top - S(5));
            }
        // the title
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAliasGridFit;
        float left = S(24);
        using (var small = new Font("Segoe UI", 11f, FontStyle.Bold))
        using (var cream = new SolidBrush(Hex("#D9CDEB")))
            g.DrawString("Tim Burton's The Nightmare Before Christmas", small, cream, left, S(14));
        var face = TitleFont();
        var style = (int)(face.IsStyleAvailable(FontStyle.Bold) ? FontStyle.Bold : FontStyle.Regular);
        float em = Math.Min(S(64), W * 0.06f);
        using (var path = new GraphicsPath())
        {
            path.AddString("Oogie's Revenge", face, style, em, new PointF(left - S(4), S(36)), StringFormat.GenericDefault);
            using (var outline = new Pen(Hex("#07050B"), S(8)) { LineJoin = LineJoin.Round }) g.DrawPath(outline, path);
            using (var rim = new Pen(Oogie, S(3)) { LineJoin = LineJoin.Round }) g.DrawPath(rim, path);
            using var fill = new LinearGradientBrush(new RectangleF(0, S(40), 10, em), Gold, Pumpkin, LinearGradientMode.Vertical);
            g.FillPath(fill, path);
        }
        using var credit = new Font("Segoe UI", 10f, FontStyle.Bold);
        using var moonInk = new SolidBrush(Moon);
        g.DrawString("PC port  -  made by JosiahG", credit, moonInk, left, S(40) + em * 1.25f);
    }

    void PaintHeader(object? sender, PaintEventArgs e)
    {
        var r = ((Control)sender!).ClientRectangle;
        if (r.Width <= 0 || r.Height <= 0) return;
        if (headerImage == null || headerImage.Size != r.Size) BuildHeader(r.Size);
        e.Graphics.DrawImageUnscaled(headerImage!, 0, 0);
    }

    // A jack-o'-lantern under the menu, its candle flickering.
    void PaintNav(object? sender, PaintEventArgs e)
    {
        var nav = (Control)sender!;
        var g = e.Graphics;
        g.SmoothingMode = SmoothingMode.AntiAlias;
        navArtTop = pages.Count > 0 ? pages[^1].button.Bottom + S(10) : 0;
        int bottom = nav.ClientSize.Height - S(16), room = bottom - navArtTop;
        if (room < S(90)) return;
        float size = Math.Min(S(150), room - S(10)), cx = (nav.Width + S(16)) / 2f, cy = bottom - size * 0.45f;
        float flicker = (float)(0.75 + 0.15 * Math.Sin(T * 9.1) + 0.1 * Math.Sin(T * 23.7));
        // glow on the ground
        using (var glow = new SolidBrush(Color.FromArgb((int)(60 * flicker), Pumpkin)))
            g.FillEllipse(glow, cx - size * 0.8f, cy - size * 0.55f, size * 1.6f, size * 1.15f);
        // the pumpkin: three overlapping lobes and a stem
        float w = size * 0.95f, h = size * 0.72f;
        using (var body = new LinearGradientBrush(new RectangleF(cx - w / 2, cy - h / 2, w, h), Hex("#F28A2E"), Hex("#B4520F"), LinearGradientMode.Vertical))
        {
            g.FillEllipse(body, cx - w / 2, cy - h / 2, w * 0.62f, h);
            g.FillEllipse(body, cx - w * 0.12f, cy - h / 2, w * 0.62f, h);
            g.FillEllipse(body, cx - w * 0.28f, cy - h / 2 - S(2), w * 0.56f, h + S(4));
        }
        using (var ribs = new Pen(Color.FromArgb(90, Hex("#7A3608")), S(2)))
        {
            g.DrawArc(ribs, cx - w * 0.18f, cy - h / 2, w * 0.36f, h, 100, 160);
            g.DrawArc(ribs, cx - w * 0.18f, cy - h / 2, w * 0.36f, h, -80, 160);
        }
        using (var stem = new SolidBrush(Oogie)) g.FillRectangle(stem, cx - S(4), cy - h / 2 - S(12), S(8), S(14));
        // the face, lit from inside
        var lit = Color.FromArgb(Lerp(200, 255, flicker), Lerp(150, 230, flicker), Lerp(40, 110, flicker));
        using var light = new SolidBrush(lit);
        PointF[] Eye(float ex) => new[] { new PointF(ex - w * 0.09f, cy - h * 0.02f), new PointF(ex + w * 0.09f, cy - h * 0.02f), new PointF(ex, cy - h * 0.24f) };
        g.FillPolygon(light, Eye(cx - w * 0.17f));
        g.FillPolygon(light, Eye(cx + w * 0.17f));
        g.FillPolygon(light, new[] { new PointF(cx - w * 0.06f, cy + h * 0.04f), new PointF(cx + w * 0.06f, cy + h * 0.04f), new PointF(cx, cy - h * 0.06f) });
        using (var mouth = new GraphicsPath())
        {
            mouth.AddLines(new[] {
                new PointF(cx - w * 0.30f, cy + h * 0.10f), new PointF(cx - w * 0.18f, cy + h * 0.16f), new PointF(cx - w * 0.12f, cy + h * 0.10f),
                new PointF(cx - w * 0.04f, cy + h * 0.18f), new PointF(cx + w * 0.04f, cy + h * 0.10f), new PointF(cx + w * 0.12f, cy + h * 0.18f),
                new PointF(cx + w * 0.18f, cy + h * 0.10f), new PointF(cx + w * 0.30f, cy + h * 0.10f), new PointF(cx + w * 0.16f, cy + h * 0.32f),
                new PointF(cx - w * 0.16f, cy + h * 0.32f) });
            mouth.CloseFigure();
            g.FillPath(light, mouth);
        }
    }

    // ----- Shared pieces -----
    // A paper card holding one page's controls, top to bottom.
    static (Panel card, FlowLayoutPanel body) NewCard(string heading)
    {
        var card = new BufferedPanel { Padding = S(22, 16, 22, 16) };
        card.Paint += (sender, e) =>
        {
            var g = e.Graphics;
            g.SmoothingMode = SmoothingMode.AntiAlias;
            var r = ((Control)sender!).ClientRectangle;
            r.Width -= S(8); r.Height -= S(8);
            r.Offset(S(2), S(2));
            using var path = Rounded(r, S(14));
            using var shadow = Rounded(new Rectangle(r.X + S(5), r.Y + S(5), r.Width, r.Height), S(14));
            using (var shade = new SolidBrush(Color.FromArgb(50, 0, 0, 0))) g.FillPath(shade, shadow);
            using (var paper = new SolidBrush(Paper)) g.FillPath(paper, path);
            using (var border = new Pen(Ink, S(3))) g.DrawPath(border, path);
        };
        var body = new FlowLayoutPanel { Dock = DockStyle.Top, AutoSize = true, AutoSizeMode = AutoSizeMode.GrowAndShrink, FlowDirection = FlowDirection.TopDown, WrapContents = false, BackColor = Paper };
        card.AutoScroll = true;
        body.Controls.Add(new Label { Text = heading, Font = new Font("Segoe UI", 18f, FontStyle.Bold), ForeColor = Ink, AutoSize = true, Margin = S(0, 0, 0, 10) });
        card.Controls.Add(body);
        return (card, body);
    }

    static GraphicsPath Rounded(Rectangle r, int radius)
    {
        var p = new GraphicsPath();
        int d = Math.Max(2, radius * 2);
        p.AddArc(r.X, r.Y, d, d, 180, 90);
        p.AddArc(r.Right - d, r.Y, d, d, 270, 90);
        p.AddArc(r.Right - d, r.Bottom - d, d, d, 0, 90);
        p.AddArc(r.X, r.Bottom - d, d, d, 90, 90);
        p.CloseFigure();
        return p;
    }

    static Label Note(string text, int width = 680) => new()
    {
        Text = text, AutoSize = true, MaximumSize = new Size(S(width), 0), ForeColor = Ink, Margin = S(0, 6, 0, 6),
    };

    static Button Btn(string text, EventHandler onClick, Color? back = null)
    {
        var b = new Button
        {
            Text = text, AutoSize = true, FlatStyle = FlatStyle.Flat, BackColor = back ?? Gold, ForeColor = Ink,
            Font = new Font("Segoe UI", 10.5f, FontStyle.Bold), Padding = S(10, 4, 10, 4), Margin = S(0, 6, 10, 6), Cursor = Cursors.Hand,
        };
        b.FlatAppearance.BorderColor = Ink;
        b.FlatAppearance.BorderSize = S(2);
        b.Click += onClick;
        return b;
    }

    static void OpenFolder(string dir) => Process.Start("explorer.exe", Directory.CreateDirectory(dir).FullName);

    // ----- Play -----
    Control BuildPlayPage()
    {
        var (card, body) = NewCard("What's this? What's this?");
        playButton = Btn("PLAY", (_, _) => Launch(), Pumpkin);
        playButton.Font = new Font("Segoe UI", 24f, FontStyle.Bold);
        playButton.Padding = S(60, 8, 60, 8);
        body.Controls.Add(playButton);
        playStatus = Note("");
        playStatus.Font = new Font("Segoe UI", 10.5f, FontStyle.Bold);
        body.Controls.Add(playStatus);
        chooseDisc = Btn("Choose your disc image (.iso) or game folder...", async (_, _) => await ChooseDisc(), Paper);
        body.Controls.Add(chooseDisc);
        progress = new ProgressBar { Width = S(520), Height = S(16), Visible = false, Margin = S(0, 4, 0, 6) };
        body.Controls.Add(progress);
        body.Controls.Add(dumpHelp = Note(
            "This port runs your own copy of The Nightmare Before Christmas: Oogie's Revenge for the original Xbox (USA). " +
            "Make a disc image of the game you own (a Redump-style .iso or an xiso), or point to a folder already extracted from it " +
            "(the one holding default.xbe), and choose it above. The launcher copies the game files into the game folder once; " +
            "the image isn't needed afterwards. No game data comes with this download."));
        body.Controls.Add(Note("In the game, F11 (or Alt+Enter) switches between fullscreen and a window. Settings changed here apply the next time the game starts."));
        var tipRow = new FlowLayoutPanel { AutoSize = true, Margin = S(0, 10, 0, 6) };
        tipLabel = new Label
        {
            AutoSize = true, MaximumSize = new Size(S(640), 0), BackColor = PurpleLight, ForeColor = Ink,
            BorderStyle = BorderStyle.FixedSingle, Padding = S(10, 8, 10, 8), Cursor = Cursors.Hand, Margin = S(0, 4, 0, 0),
        };
        tipLabel.Click += (_, _) => NextTip();
        tipRow.Controls.Add(tipLabel);
        tipIndex = Random.Shared.Next(Tips.Length) - 1;
        NextTip();
        body.Controls.Add(tipRow);
        var row = new FlowLayoutPanel { AutoSize = true, Margin = Padding.Empty };
        row.Controls.Add(Btn("Open game folder", (_, _) => OpenFolder(gameDir), Paper));
        row.Controls.Add(Btn("Open saves and settings", (_, _) => OpenFolder(userData), Paper));
        body.Controls.Add(row);
        return card;
    }

    static readonly string[] Tips =
    {
        "The game draws at 4K by default and fits any screen, sharp on every display.",
        "F11 or Alt+Enter flips the game between fullscreen and a window.",
        "Any Xbox-style gamepad works as the Xbox controller right away.",
        "Saves live in UserData\\hdd. A backup now and then never hurts.",
        "Shaders are prepared the first time each effect appears, then kept: later visits are smooth.",
        "Keyboard players: the Controls page lets you move every button to the key you like.",
        "Click here for another tip. This is Halloween, after all.",
    };
    Label? tipLabel;
    int tipIndex;

    void NextTip()
    {
        tipIndex = (tipIndex + 1) % Tips.Length;
        if (tipLabel != null) tipLabel.Text = "Tip: " + Tips[tipIndex];
    }

    (bool ok, string text) DiscState()
    {
        var xbe = Path.Combine(discDir, "default.xbe");
        if (!File.Exists(xbe)) return (false, "No game set up yet. Choose your Oogie's Revenge disc image below.");
        string hash;
        try { using var f = File.OpenRead(xbe); hash = Convert.ToHexString(System.Security.Cryptography.SHA256.HashData(f)); }
        catch (Exception e) { return (false, "The game files can't be read: " + e.Message); }
        return hash.Equals(XboxDisc.WantedXbeSha256, StringComparison.OrdinalIgnoreCase)
            ? (true, "Oogie's Revenge (USA) is ready. Let's make this Christmas... spooky.")
            : (false, "The game folder holds a different game or version. Choose the USA Oogie's Revenge disc image again.");
    }

    void RefreshDisc()
    {
        if (playStatus == null) return;
        var (ok, text) = DiscState();
        playStatus.Text = text;
        playStatus.ForeColor = ok ? Good : Warn;
        playButton.Enabled = ok && File.Exists(exePath);
        if (!playButton.Enabled) playButton.BackColor = Hex("#D8CFC0");
        chooseDisc.Text = ok ? "Change disc image or game folder..." : "Choose your disc image (.iso) or game folder...";
        dumpHelp.Visible = !ok;
    }

    async Task ChooseDisc()
    {
        using var dialog = new OpenFileDialog
        {
            Title = "Choose your Oogie's Revenge disc image (or default.xbe in an extracted game folder)",
            Filter = "Xbox disc image or game (*.iso;*.xiso;default.xbe)|*.iso;*.xiso;default.xbe|All files (*.*)|*.*",
        };
        if (dialog.ShowDialog(this) != DialogResult.OK) return;
        var staging = discDir + ".new";
        chooseDisc.Enabled = playButton.Enabled = false;
        progress.Visible = true; progress.Value = 0;
        var report = new Progress<(int done, int total, string name)>(p =>
        {
            progress.Maximum = Math.Max(1, p.total); progress.Value = Math.Min(p.done, progress.Maximum);
            playStatus.Text = $"Copying the game files {p.done}/{p.total}: {p.name}";
        });
        try
        {
            if (Directory.Exists(staging)) Directory.Delete(staging, true);
            if (Path.GetFileName(dialog.FileName).Equals("default.xbe", StringComparison.OrdinalIgnoreCase))
                await Task.Run(() => CopyExtracted(Path.GetDirectoryName(dialog.FileName)!, staging, report));
            else
                await Task.Run(() =>
                {
                    using var disc = XboxDisc.Open(dialog.FileName);
                    var problem = disc.Problem();
                    if (problem.Length > 0) throw new InvalidDataException(problem);
                    disc.Extract(staging, (d, t, n) => ((IProgress<(int, int, string)>)report).Report((d, t, n)));
                });
            if (Directory.Exists(discDir)) Directory.Delete(discDir, true);
            Directory.CreateDirectory(Path.GetDirectoryName(discDir)!);
            Directory.Move(staging, discDir);
        }
        catch (Exception e)
        {
            try { if (Directory.Exists(staging)) Directory.Delete(staging, true); } catch { }
            MessageBox.Show(this, e is InvalidDataException ? e.Message : "The game files could not be copied: " + e.Message, AppTitle,
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
        finally { progress.Visible = false; chooseDisc.Enabled = true; RefreshDisc(); }
    }

    // A folder extracted by another tool: checked like a disc image, then copied.
    static void CopyExtracted(string from, string to, IProgress<(int, int, string)> report)
    {
        using (var f = File.OpenRead(Path.Combine(from, "default.xbe")))
            if (!Convert.ToHexString(System.Security.Cryptography.SHA256.HashData(f)).Equals(XboxDisc.WantedXbeSha256, StringComparison.OrdinalIgnoreCase))
                throw new InvalidDataException("This is not The Nightmare Before Christmas: Oogie's Revenge for the Xbox (USA). " +
                                               "Only that version runs, because the port was built from its exact game code.");
        var files = Directory.GetFiles(from, "*", SearchOption.AllDirectories);
        int done = 0;
        foreach (var file in files)
        {
            var rel = Path.GetRelativePath(from, file);
            var target = Path.Combine(to, rel);
            Directory.CreateDirectory(Path.GetDirectoryName(target)!);
            File.Copy(file, target, true);
            report.Report((++done, files.Length, rel));
        }
    }

    void Launch()
    {
        if (!File.Exists(exePath)) { MessageBox.Show(this, "The game program (data\\" + GameExe + ") is missing. Unzip the whole download again.", AppTitle); return; }
        Process.Start(new ProcessStartInfo(exePath) { WorkingDirectory = gameDir, UseShellExecute = true });
        WindowState = FormWindowState.Minimized;
    }

    // ----- Display -----
    Control BuildDisplayPage()
    {
        var (card, body) = NewCard("Display and sound");
        var table = new TableLayoutPanel { AutoSize = true, ColumnCount = 2, BackColor = Paper, Margin = S(0, 4, 0, 8) };
        void Row(string label, string section, string key, (string text, string raw)[] options, string fallback)
        {
            var box = new ComboBox { DropDownStyle = ComboBoxStyle.DropDownList, Width = S(360), Cursor = Cursors.Hand };
            foreach (var o in options) box.Items.Add(o.text);
            var current = new GameConfig(configPath).Get(section, key) ?? fallback;
            int index = Array.FindIndex(options, o => o.raw.Trim('"') == current.Trim('"'));
            box.SelectedIndex = index >= 0 ? index : Array.FindIndex(options, o => o.raw.Trim('"') == fallback);
            box.SelectedIndexChanged += (_, _) =>
            {
                var c = new GameConfig(configPath);
                c.Set(section, key, options[box.SelectedIndex].raw);
                c.Save();
            };
            table.Controls.Add(new Label { Text = label, AutoSize = true, ForeColor = Ink, Font = new Font("Segoe UI", 10.5f, FontStyle.Bold), Margin = S(0, 10, 16, 8) });
            table.Controls.Add(box);
        }
        Row("Window", "display", "fullscreen", new[] { ("Window", "false"), ("Fullscreen", "true") }, "false");
        Row("Resolution", "display", "resolution", new[] { ("Original (480 lines)", "\"original\""), ("720p", "\"720\""), ("1080p", "\"1080\""),
                ("1440p", "\"1440\""), ("4K (best)", "\"4k\""), ("Your screen's size", "\"screen\"") }, "4k");
        Row("Picture shape", "display", "aspect", new[] { ("Your screen's shape (default)", "\"auto\""), ("Original 4:3", "\"4:3\""),
                ("Widescreen 16:9", "\"16:9\""), ("Widescreen 16:10", "\"16:10\""), ("Ultrawide 21:9", "\"21:9\""),
                ("Super ultrawide 32:9", "\"32:9\""), ("Stretch 4:3 to fill the screen", "\"stretch\"") }, "auto");
        Row("Frame rate", "display", "fps", new[] { ("Match the screen (default)", "\"auto\""), ("60 (original)", "\"60\""),
                ("120 (smooth in-between frames)", "\"120\"") }, "auto");
        Row("Ray tracing", "display", "ray_tracing", new[] { ("On: ray-traced ambient occlusion (default)", "true"), ("Off", "false") }, "true");
        Row("Frame rate in the title bar", "display", "show_fps", new[] { ("Off", "false"), ("On", "true") }, "false");
        Row("Volume", "audio", "volume", new[] { ("Louder (200%)", "200"), ("Loud (150%)", "150"), ("Original Xbox level (default)", "100"),
                ("50%", "50"), ("25%", "25"), ("Off", "0") }, "100");
        Row("Music", "audio", "music", new[] { ("As the game mixes it (default)", "100"), ("Softer (70%)", "70"), ("Quiet (50%)", "50"),
                ("Very quiet (30%)", "30"), ("Off", "0") }, "100");
        body.Controls.Add(table);
        body.Controls.Add(Note("Changes are saved at once and apply the next time the game starts. The game itself runs at the Xbox's " +
                               "60 steps per second; at 120 frames per second (chosen automatically on a 120 Hz or faster screen) a " +
                               "picture halfway between each two steps is shown as well, so motion is smoother. A higher resolution makes the picture sharper on any screen (4K looks best even on a " +
                               "1080p monitor). A wider picture shape shows more of the world at the sides; menus, the HUD and " +
                               "movies keep their 4:3 shape. Ray tracing traces rays through each frame's depth to darken corners, creases and the " +
                               "ground under characters, as the light reaching them is blocked. F11 or Alt+Enter switches between fullscreen and a window while playing."));
        return card;
    }

    // ----- Controls -----
    static readonly (string key, string what, string fallback)[] Bindings =
    {
        ("move_up", "Move up", "W"), ("move_down", "Move down", "S"), ("move_left", "Move left", "A"), ("move_right", "Move right", "D"),
        ("camera_up", "Camera up", "Up"), ("camera_down", "Camera down", "Down"), ("camera_left", "Camera left", "Left"), ("camera_right", "Camera right", "Right"),
        ("a", "A", "Space"), ("b", "B", "LShift"), ("x", "X", "R"), ("y", "Y", "F"), ("black", "Black", "1"), ("white", "White", "2"),
        ("left_trigger", "Left trigger", "Q"), ("right_trigger", "Right trigger", "E"), ("start", "Start (pause)", "Enter"), ("back", "Back", "Tab"),
        ("dpad_up", "D-pad up", "I"), ("dpad_down", "D-pad down", "K"), ("dpad_left", "D-pad left", "J"), ("dpad_right", "D-pad right", "L"),
        ("left_stick_click", "Left stick click", "LCtrl"), ("right_stick_click", "Right stick click", "C"),
    };

    // The PC controller's buttons, in the order of the Xbox buttons they stand for by default ([gamepad], config.cpp)
    static readonly string[] PadButtons = { "A", "B", "X", "Y", "RB", "LB", "LT", "RT", "Start", "Back", "Up", "Down", "Left", "Right", "LS", "RS" };
    static readonly string[] PadButtonText = { "A", "B", "X", "Y", "RB (right bumper)", "LB (left bumper)", "LT (left trigger)", "RT (right trigger)",
        "Start / Menu", "Back / View", "D-pad up", "D-pad down", "D-pad left", "D-pad right", "Left stick click", "Right stick click" };

    Control BuildControlsPage()
    {
        var (card, body) = NewCard("Controls");
        body.Controls.Add(Note("Gamepads (Xbox, or any XInput controller) work right away as the Xbox controller; below, each Xbox button " +
                               "can come from another button of yours. The sticks stay as they are. " +
                               "For the keyboard, click a key below and press the one you want (Esc cancels, Delete leaves it unbound)."));
        var pads = new TableLayoutPanel { AutoSize = true, ColumnCount = 4, BackColor = Paper, Margin = S(0, 8, 0, 8) };
        var boxes = new List<(ComboBox box, string key, int fallback)>();
        foreach (var (key, what, _) in Bindings.Skip(8))  // the 16 Xbox buttons, from "a" on
        {
            int fallback = boxes.Count;
            var box = new ComboBox { DropDownStyle = ComboBoxStyle.DropDownList, Width = S(170), Cursor = Cursors.Hand };
            box.Items.AddRange(PadButtonText);
            box.Items.Add("(none)");
            box.SelectionChangeCommitted += (_, _) =>
            {
                var c = new GameConfig(configPath);
                c.SetString("gamepad", key, box.SelectedIndex < PadButtons.Length ? PadButtons[box.SelectedIndex] : "none");
                c.Save();
            };
            pads.Controls.Add(new Label { Text = "Xbox " + what, AutoSize = true, ForeColor = Ink, Margin = S(0, 10, 10, 6) });
            pads.Controls.Add(box);
            boxes.Add((box, key, fallback));
        }
        void FillPad()
        {
            var c = new GameConfig(configPath);
            foreach (var (box, key, fallback) in boxes)
            {
                var v = c.Get("gamepad", key);
                int i = v == null ? fallback : Array.FindIndex(PadButtons, b => string.Equals(b, v, StringComparison.OrdinalIgnoreCase));
                box.SelectedIndex = i >= 0 ? i : PadButtons.Length;
            }
        }
        FillPad();
        body.Controls.Add(pads);
        body.Controls.Add(Btn("Reset the gamepad to the defaults", (_, _) =>
        {
            var c = new GameConfig(configPath);
            foreach (var (_, key, _) in boxes) c.Remove("gamepad", key);
            c.Save();
            FillPad();
        }, Paper));
        var table = new TableLayoutPanel { AutoSize = true, ColumnCount = 4, BackColor = Paper, Margin = S(0, 8, 0, 8) };
        var buttons = new List<(Button button, string key, string fallback)>();
        foreach (var (key, what, fallback) in Bindings)
        {
            table.Controls.Add(new Label { Text = what, AutoSize = true, ForeColor = Ink, Margin = S(0, 10, 10, 6) });
            var b = Btn("", (_, _) => { }, Paper);
            b.MinimumSize = S(120, 0);
            b.Click += (_, _) =>
            {
                var name = KeyCapture.Ask(this, what);
                if (name == null) return;
                var c = new GameConfig(configPath);
                c.SetString("keyboard", key, name.Length == 0 ? "none" : name);
                c.Save();
                b.Text = name.Length == 0 ? "(none)" : name;
            };
            buttons.Add((b, key, fallback));
            table.Controls.Add(b);
        }
        void Fill()
        {
            var c = new GameConfig(configPath);
            foreach (var (b, key, fallback) in buttons)
            {
                var v = c.Get("keyboard", key) ?? fallback;
                b.Text = v == "none" || v.Length == 0 ? "(none)" : v;
            }
        }
        Fill();
        body.Controls.Add(table);
        body.Controls.Add(Btn("Reset the keyboard to the defaults", (_, _) =>
        {
            var c = new GameConfig(configPath);
            foreach (var (key, _, _) in Bindings) c.Remove("keyboard", key);
            c.Save();
            Fill();
        }, Paper));
        return card;
    }

    // ----- Mods -----
    Control BuildModsPage()
    {
        var (card, body) = NewCard("Mods");
        body.Controls.Add(Note("A mod is a folder in UserData\\mods. Its files\\ folder mirrors the game's files: a file there is used " +
                               "instead of the game's own one (for example files\\movie\\<name>.bik for an upscaled movie in the same Bink format). " +
                               "Untick a mod to switch it off; when two mods change the same file, the later name wins."));
        var list = new CheckedListBox { Width = S(520), Height = S(220), CheckOnClick = true, BorderStyle = BorderStyle.FixedSingle, Margin = S(0, 8, 0, 8) };
        void Fill()
        {
            list.Items.Clear();
            if (!Directory.Exists(modsDir)) return;
            foreach (var d in Directory.GetDirectories(modsDir).Where(d => Path.GetFileName(d) != "files").OrderBy(d => d, StringComparer.OrdinalIgnoreCase))
                list.Items.Add(Path.GetFileName(d), !File.Exists(Path.Combine(d, "disabled")));
        }
        list.ItemCheck += (_, e) =>
        {
            var flag = Path.Combine(modsDir, (string)list.Items[e.Index], "disabled");
            if (e.NewValue == CheckState.Checked) File.Delete(flag); else File.WriteAllText(flag, "");
        };
        body.Controls.Add(list);
        var row = new FlowLayoutPanel { AutoSize = true, Margin = Padding.Empty };
        row.Controls.Add(Btn("Open the mods folder", (_, _) => OpenFolder(modsDir), Paper));
        row.Controls.Add(Btn("Refresh", (_, _) => Fill(), Paper));
        body.Controls.Add(row);
        Fill();
        return card;
    }
}

// A small dialog that waits for one key and returns its name as Config.toml spells it ("" = unbound, null = cancelled).
sealed class KeyCapture : Form
{
    [DllImport("user32.dll")] static extern short GetAsyncKeyState(int vk);
    string? result;

    KeyCapture(string what)
    {
        Text = "Press a key";
        FormBorderStyle = FormBorderStyle.FixedDialog;
        MaximizeBox = MinimizeBox = false;
        StartPosition = FormStartPosition.CenterParent;
        KeyPreview = true;
        AutoSize = true;
        Padding = new Padding(24);
        Controls.Add(new Label { Text = $"Press the key for \"{what}\".\nEsc cancels, Delete leaves it unbound.", AutoSize = true, Font = new Font("Segoe UI", 11f) });
    }

    protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
    {
        var key = keyData & Keys.KeyCode;
        if (key == Keys.Escape) { Close(); return true; }
        if (key == Keys.Delete) { result = ""; Close(); return true; }
        var name = KeyName(key);
        if (name != null) { result = name; Close(); }
        return true;
    }

    // The runtime's key names (xboxrecomp/runtime/config.cpp key_code); null for keys it does not take.
    static string? KeyName(Keys k)
    {
        if (k >= Keys.A && k <= Keys.Z) return ((char)('A' + (k - Keys.A))).ToString();
        if (k >= Keys.D0 && k <= Keys.D9) return ((char)('0' + (k - Keys.D0))).ToString();
        if (k >= Keys.NumPad0 && k <= Keys.NumPad9) return "Num" + (k - Keys.NumPad0);
        if (k >= Keys.F1 && k <= Keys.F12 && k != Keys.F10 && k != Keys.F11) return "F" + (k - Keys.F1 + 1);
        return k switch
        {
            Keys.ShiftKey => (GetAsyncKeyState(0xA1) & 0x8000) != 0 ? "RShift" : "LShift",
            Keys.ControlKey => (GetAsyncKeyState(0xA3) & 0x8000) != 0 ? "RCtrl" : "LCtrl",
            Keys.Menu => (GetAsyncKeyState(0xA5) & 0x8000) != 0 ? "RAlt" : "LAlt",
            Keys.Space => "Space", Keys.Enter => "Enter", Keys.Tab => "Tab", Keys.Back => "Backspace",
            Keys.Up => "Up", Keys.Down => "Down", Keys.Left => "Left", Keys.Right => "Right",
            Keys.Insert => "Insert", Keys.Home => "Home", Keys.End => "End", Keys.PageUp => "PageUp", Keys.PageDown => "PageDown",
            Keys.Oemcomma => "Comma", Keys.OemPeriod => "Period", Keys.OemQuestion => "Slash", Keys.OemSemicolon => "Semicolon",
            Keys.OemQuotes => "Quote", Keys.OemOpenBrackets => "LBracket", Keys.OemCloseBrackets => "RBracket",
            Keys.OemMinus => "Minus", Keys.Oemplus => "Equals", Keys.OemPipe => "Backslash", Keys.Oemtilde => "Backquote",
            _ => null,
        };
    }

    public static string? Ask(IWin32Window owner, string what)
    {
        using var f = new KeyCapture(what);
        f.ShowDialog(owner);
        return f.result;
    }
}

sealed class BufferedPanel : Panel
{
    public BufferedPanel() { DoubleBuffered = true; ResizeRedraw = true; }
}

sealed class BufferedFlow : FlowLayoutPanel
{
    public BufferedFlow() { DoubleBuffered = true; ResizeRedraw = true; }
}
