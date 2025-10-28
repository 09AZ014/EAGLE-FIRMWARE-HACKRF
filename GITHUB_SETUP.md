# 🦅 EAGLE-FIRMWARE - GitHub Setup Guide

## 📦 Initial Setup Complete

Your EAGLE-FIRMWARE repository is ready to be pushed to GitHub!

### ✅ What's Done
- ✓ Git repository initialized
- ✓ All files committed (3758 files)
- ✓ README_EAGLE.md created with full documentation
- ✓ GitHub Actions workflow configured
- ✓ New apps added (RF Signal Mapper, Protocol Decoder Pro)
- ✓ .gitignore configured

---

## 🚀 Quick Start - Push to GitHub

### Option 1: Automated (Recommended)

Run the setup script:
```powershell
cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'
.\setup_github.ps1
```

This will:
- Check for GitHub CLI
- Create the repository automatically
- Push all code
- Set up remote origin

### Option 2: Manual Setup

1. **Install GitHub CLI (if not installed)**
   - Download: https://cli.github.com/
   - Run installer
   - Restart PowerShell

2. **Authenticate with GitHub**
   ```powershell
   gh auth login
   ```
   - Choose: GitHub.com
   - Choose: HTTPS
   - Authenticate: Login with browser

3. **Create Repository**
   ```powershell
   cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'
   gh repo create eagle-firmware --public --source=. --remote=origin
   ```

4. **Rename branch to main**
   ```powershell
   git branch -M main
   ```

5. **Push to GitHub**
   ```powershell
   git push -u origin main
   ```

### Option 3: Via GitHub Web Interface

1. Go to: https://github.com/new

2. Create repository:
   - Name: `eagle-firmware`
   - Description: `🦅 EAGLE-FIRMWARE - Advanced PortaPack Mayhem Fork`
   - Visibility: **Public**
   - **DO NOT** initialize with README/license/.gitignore

3. After creating, run:
   ```powershell
   cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'
   git remote add origin https://github.com/YOUR_USERNAME/eagle-firmware.git
   git branch -M main
   git push -u origin main
   ```

---

## 🔄 Future Commits

After initial setup, use these commands for updates:

```powershell
# Check status
git status

# Add changes
git add .

# Commit
git commit -m "Your commit message"

# Push to GitHub
git push
```

### Commit Message Examples
```
✨ Add new spectrum waterfall feature
🐛 Fix RF mapper crash on H2M
📝 Update installation instructions
🎮 Improve Snake game performance
🔧 Optimize build configuration
```

---

## 📋 After First Push

### 1. Repository Settings
Go to: `https://github.com/YOUR_USERNAME/eagle-firmware/settings`

**Topics to add:**
- hackrf
- portapack
- firmware
- sdr
- rf
- eagle
- hackrf-one
- mayhem

### 2. Enable GitHub Actions
Go to: `https://github.com/YOUR_USERNAME/eagle-firmware/actions`
- Click "I understand my workflows, go ahead and enable them"

### 3. Create Releases
When ready to release:
```powershell
git tag -a v2.0.0 -m "EAGLE-FIRMWARE v2.0.0"
git push origin v2.0.0
```

Then on GitHub:
- Go to Releases
- Click "Draft a new release"
- Choose tag: v2.0.0
- Title: `🦅 EAGLE-FIRMWARE v2.0.0`
- Description: Copy from README_EAGLE.md changelog
- Upload compiled .bin files
- Publish release

### 4. Add Repository Banner
1. Create a banner image (1280x640px recommended)
2. Upload to repository
3. Edit README_EAGLE.md to add at top:
   ```markdown
   ![EAGLE-FIRMWARE Banner](banner.png)
   ```

---

## 🔧 Repository Structure

```
eagle-firmware/
├── .github/
│   └── workflows/
│       └── build_eagle.yml    # CI/CD automation
├── firmware/
│   ├── application/
│   │   ├── apps/              # Core apps
│   │   └── external/          # New apps
│   │       ├── rf_mapper/     # ✨ NEW
│   │       └── protocol_decoder/  # ✨ NEW
├── README_EAGLE.md            # Main documentation
├── GITHUB_SETUP.md            # This file
├── setup_github.ps1           # Setup script
└── CMakeLists.txt
```

---

## 📊 GitHub Actions

Your repository includes automatic build on:
- Push to `main` or `develop`
- Pull requests
- New releases

**Artifacts generated:**
- Compiled .bin firmware files
- Build logs
- Release packages

---

## 🆘 Troubleshooting

### "gh: command not found"
**Solution:** Install GitHub CLI from https://cli.github.com/

### "Authentication required"
**Solution:** Run `gh auth login`

### "Repository already exists"
**Solution:** Use a different name or delete the existing repo first

### Large file warnings
**Solution:** Some files might be large. GitHub has a 100MB limit per file.
If needed, use Git LFS:
```powershell
git lfs install
git lfs track "*.bin"
git add .gitattributes
```

### Submodule warnings
The `hackrf/` folder is a git submodule. This is normal and expected.

---

## 📝 Best Practices

### Branching Strategy
```
main        → Production-ready releases
develop     → Development/testing
feature/*   → New features
bugfix/*    → Bug fixes
```

### Before Committing
1. Test changes on hardware
2. Run build locally
3. Update README if adding features
4. Write clear commit messages

### Commit Frequency
- Commit after each significant change
- Push to GitHub at least daily
- Create releases for stable versions

---

## 🎯 Next Steps

1. ✅ Push code to GitHub
2. ⬜ Enable GitHub Actions
3. ⬜ Add repository topics
4. ⬜ Create first release (v2.0.0)
5. ⬜ Share with community
6. ⬜ Accept contributions via PRs

---

## 📞 Support

- GitHub Issues: Report bugs and request features
- Discussions: Community questions and ideas
- Pull Requests: Code contributions welcome!

---

**Made with ❤️ by 09AZO14**

🦅 **Fly Higher with EAGLE** 🦅

