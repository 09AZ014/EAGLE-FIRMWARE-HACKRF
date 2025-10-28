# EAGLE-FIRMWARE - GitHub Setup Script
# By 09AZO14

Write-Host "🦅 EAGLE-FIRMWARE - GitHub Repository Setup" -ForegroundColor Cyan
Write-Host "=============================================" -ForegroundColor Cyan
Write-Host ""

# Check if GitHub CLI is installed
$ghInstalled = Get-Command gh -ErrorAction SilentlyContinue

if ($ghInstalled) {
    Write-Host "✓ GitHub CLI detected" -ForegroundColor Green
    Write-Host ""
    
    # Check if authenticated
    $authStatus = gh auth status 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "⚠ You need to authenticate with GitHub CLI first" -ForegroundColor Yellow
        Write-Host "Run: gh auth login" -ForegroundColor Yellow
        Write-Host ""
        exit 1
    }
    
    Write-Host "✓ GitHub CLI authenticated" -ForegroundColor Green
    Write-Host ""
    
    # Get repository details
    $repoName = Read-Host "Enter repository name (default: eagle-firmware)"
    if ([string]::IsNullOrWhiteSpace($repoName)) {
        $repoName = "eagle-firmware"
    }
    
    $repoVisibility = Read-Host "Repository visibility? (public/private) [default: public]"
    if ([string]::IsNullOrWhiteSpace($repoVisibility)) {
        $repoVisibility = "public"
    }
    
    $description = "🦅 EAGLE-FIRMWARE - Advanced PortaPack Mayhem Fork with RF Signal Mapper, Protocol Decoder Pro, and 8+ Games"
    
    Write-Host ""
    Write-Host "Creating GitHub repository..." -ForegroundColor Yellow
    
    # Create repository
    gh repo create $repoName --$repoVisibility --description "$description" --source=. --remote=origin --push
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "✓ Repository created successfully!" -ForegroundColor Green
        Write-Host ""
        Write-Host "Repository URL: https://github.com/$(gh api user --jq .login)/$repoName" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "Next steps:" -ForegroundColor Yellow
        Write-Host "1. Visit your repository on GitHub" -ForegroundColor White
        Write-Host "2. Enable GitHub Actions in repository settings" -ForegroundColor White
        Write-Host "3. Add repository topics: hackrf, portapack, firmware, sdr, rf" -ForegroundColor White
        Write-Host "4. Add a repository banner/logo" -ForegroundColor White
        Write-Host ""
    } else {
        Write-Host "✗ Failed to create repository" -ForegroundColor Red
        exit 1
    }
    
} else {
    Write-Host "⚠ GitHub CLI not found" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "MANUAL SETUP INSTRUCTIONS:" -ForegroundColor Cyan
    Write-Host "===========================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "1. Go to: https://github.com/new" -ForegroundColor White
    Write-Host ""
    Write-Host "2. Fill in repository details:" -ForegroundColor White
    Write-Host "   - Repository name: eagle-firmware" -ForegroundColor Gray
    Write-Host "   - Description: 🦅 EAGLE-FIRMWARE - Advanced PortaPack Mayhem Fork" -ForegroundColor Gray
    Write-Host "   - Visibility: Public (recommended)" -ForegroundColor Gray
    Write-Host "   - Initialize: UNCHECK all options (we already have code)" -ForegroundColor Gray
    Write-Host ""
    Write-Host "3. Click 'Create repository'" -ForegroundColor White
    Write-Host ""
    Write-Host "4. Copy the remote URL from GitHub" -ForegroundColor White
    Write-Host ""
    Write-Host "5. Run these commands:" -ForegroundColor White
    Write-Host "   cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'" -ForegroundColor Gray
    Write-Host "   git remote add origin <YOUR_GITHUB_URL>" -ForegroundColor Gray
    Write-Host "   git branch -M main" -ForegroundColor Gray
    Write-Host "   git push -u origin main" -ForegroundColor Gray
    Write-Host ""
    Write-Host "Alternative: Install GitHub CLI" -ForegroundColor Yellow
    Write-Host "   Download from: https://cli.github.com/" -ForegroundColor Gray
    Write-Host "   Then run this script again" -ForegroundColor Gray
    Write-Host ""
}

Write-Host ""
Write-Host "🦅 Setup complete!" -ForegroundColor Green
Write-Host ""
