# EAGLE-FIRMWARE - Automatic GitHub Repository Creator
# By 09AZO14

Write-Host "========================================================" -ForegroundColor Cyan
Write-Host "   EAGLE-FIRMWARE - GitHub Repository Creator" -ForegroundColor Cyan
Write-Host "========================================================" -ForegroundColor Cyan
Write-Host ""

# Get GitHub username
$username = Read-Host "Enter your GitHub username"

Write-Host ""
Write-Host "Creating repository for user: $username" -ForegroundColor Yellow
Write-Host ""

# Repository details
$repoName = "eagle-firmware"
$description = "🦅 EAGLE-FIRMWARE v2.0.0 - Advanced PortaPack Mayhem Fork with RF Signal Mapper, Protocol Decoder Pro, and 8+ Games"
$homepage = ""

Write-Host "Repository name: $repoName" -ForegroundColor Green
Write-Host "Description: $description" -ForegroundColor Green
Write-Host ""

# Ask for Personal Access Token
Write-Host "You need a GitHub Personal Access Token (PAT)" -ForegroundColor Yellow
Write-Host "If you don't have one:" -ForegroundColor Yellow
Write-Host "1. Go to: https://github.com/settings/tokens" -ForegroundColor Gray
Write-Host "2. Click 'Generate new token (classic)'" -ForegroundColor Gray
Write-Host "3. Select scope: 'repo' (full control)" -ForegroundColor Gray
Write-Host "4. Generate and copy the token" -ForegroundColor Gray
Write-Host ""

$token = Read-Host "Enter your GitHub Personal Access Token (PAT)" -AsSecureString
$tokenPlain = [Runtime.InteropServices.Marshal]::PtrToStringAuto([Runtime.InteropServices.Marshal]::SecureStringToBSTR($token))

# Create repository via GitHub API
Write-Host ""
Write-Host "Creating repository on GitHub..." -ForegroundColor Yellow

$headers = @{
    "Authorization" = "token $tokenPlain"
    "Accept" = "application/vnd.github.v3+json"
}

$body = @{
    "name" = $repoName
    "description" = $description
    "homepage" = $homepage
    "private" = $false
    "has_issues" = $true
    "has_projects" = $true
    "has_wiki" = $true
    "auto_init" = $false
} | ConvertTo-Json

try {
    $response = Invoke-RestMethod -Uri "https://api.github.com/user/repos" -Method Post -Headers $headers -Body $body -ContentType "application/json"
    
    Write-Host ""
    Write-Host "✓ Repository created successfully!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Repository URL: $($response.html_url)" -ForegroundColor Cyan
    Write-Host "Clone URL: $($response.clone_url)" -ForegroundColor Cyan
    Write-Host ""
    
    # Add remote and push
    Write-Host "Adding remote and pushing code..." -ForegroundColor Yellow
    
    git remote add origin $($response.clone_url)
    git branch -M main
    git push -u origin main
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "✓ Code pushed to GitHub successfully!" -ForegroundColor Green
        Write-Host ""
        Write-Host "========================================================" -ForegroundColor Cyan
        Write-Host "   NEXT STEPS:" -ForegroundColor Cyan
        Write-Host "========================================================" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "1. Visit: $($response.html_url)" -ForegroundColor White
        Write-Host "2. Go to Settings → Topics" -ForegroundColor White
        Write-Host "3. Add topics: hackrf, portapack, firmware, sdr, rf, eagle" -ForegroundColor White
        Write-Host "4. Go to Actions → Enable workflows" -ForegroundColor White
        Write-Host "5. Create first release v2.0.0" -ForegroundColor White
        Write-Host ""
        Write-Host "🦅 Repository ready! Fly Higher with EAGLE! 🦅" -ForegroundColor Green
        Write-Host ""
    } else {
        Write-Host ""
        Write-Host "⚠ Repository created but push failed" -ForegroundColor Yellow
        Write-Host "Run manually: git push -u origin main" -ForegroundColor Yellow
    }
    
} catch {
    Write-Host ""
    Write-Host "✗ Error creating repository" -ForegroundColor Red
    Write-Host "Error: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host ""
    Write-Host "MANUAL INSTRUCTIONS:" -ForegroundColor Yellow
    Write-Host "====================` " -ForegroundColor Yellow
    Write-Host "1. Go to: https://github.com/new" -ForegroundColor White
    Write-Host "2. Name: eagle-firmware" -ForegroundColor White
    Write-Host "3. Description: $description" -ForegroundColor White
    Write-Host "4. Public, no README/license" -ForegroundColor White
    Write-Host "5. Create repository" -ForegroundColor White
    Write-Host ""
    Write-Host "Then run:" -ForegroundColor White
    Write-Host "git remote add origin https://github.com/$username/$repoName.git" -ForegroundColor Gray
    Write-Host "git branch -M main" -ForegroundColor Gray
    Write-Host "git push -u origin main" -ForegroundColor Gray
    Write-Host ""
}
