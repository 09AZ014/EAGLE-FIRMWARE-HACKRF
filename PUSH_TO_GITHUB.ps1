##############################################################
#  EAGLE-FIRMWARE - ONE-CLICK GITHUB UPLOAD
#  By 09AZO14
##############################################################

Write-Host ""
Write-Host "========================================================" -ForegroundColor Cyan
Write-Host "   🦅 EAGLE-FIRMWARE - GitHub Upload" -ForegroundColor Cyan
Write-Host "========================================================" -ForegroundColor Cyan
Write-Host ""

# Step 1: Get username
Write-Host "STEP 1: GitHub Username" -ForegroundColor Yellow
Write-Host "----------------------------------------" -ForegroundColor Gray
$username = Read-Host "Enter your GitHub username"

# Step 2: Get token
Write-Host ""
Write-Host "STEP 2: Personal Access Token (PAT)" -ForegroundColor Yellow
Write-Host "----------------------------------------" -ForegroundColor Gray
Write-Host ""
Write-Host "Need a token? Quick steps:" -ForegroundColor White
Write-Host "1. Open: https://github.com/settings/tokens/new" -ForegroundColor Gray
Write-Host "2. Note: 'EAGLE-FIRMWARE Upload'" -ForegroundColor Gray
Write-Host "3. Expiration: 7 days" -ForegroundColor Gray
Write-Host "4. Check: [x] repo (full control)" -ForegroundColor Gray
Write-Host "5. Generate token → Copy it" -ForegroundColor Gray
Write-Host ""
$token = Read-Host "Paste your token here" -AsSecureString
$tokenBSTR = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($token)
$tokenPlain = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($tokenBSTR)

# Step 3: Create repository
Write-Host ""
Write-Host "STEP 3: Creating Repository" -ForegroundColor Yellow
Write-Host "----------------------------------------" -ForegroundColor Gray

$repoName = "EAGLE-FIRMWARE-HACKRF"
$description = "🦅 EAGLE-FIRMWARE v2.0.0 - Advanced PortaPack H2 Firmware with RF Signal Mapper Pro, Protocol Decoder (19 protocols), 8 Games & 61 Apps | Based on Mayhem"

$headers = @{
    "Authorization" = "Bearer $tokenPlain"
    "Accept" = "application/vnd.github+json"
    "X-GitHub-Api-Version" = "2022-11-28"
}

$body = @{
    name = $repoName
    description = $description
    homepage = ""
    private = $false
    has_issues = $true
    has_projects = $false
    has_wiki = $true
    auto_init = $false
} | ConvertTo-Json

try {
    Write-Host "Creating repository: $repoName ..." -ForegroundColor White
    
    $response = Invoke-RestMethod -Uri "https://api.github.com/user/repos" `
        -Method Post `
        -Headers $headers `
        -Body $body `
        -ContentType "application/json"
    
    Write-Host "✓ Repository created!" -ForegroundColor Green
    Write-Host ""
    Write-Host "URL: $($response.html_url)" -ForegroundColor Cyan
    Write-Host ""
    
    # Step 4: Push code
    Write-Host "STEP 4: Uploading Code" -ForegroundColor Yellow
    Write-Host "----------------------------------------" -ForegroundColor Gray
    
    $repoUrl = $response.clone_url
    
    # Remove existing remote if exists
    git remote remove origin 2>$null
    
    # Add new remote
    Write-Host "Adding remote..." -ForegroundColor White
    git remote add origin $repoUrl
    
    # Rename branch
    Write-Host "Preparing branch..." -ForegroundColor White
    git branch -M main
    
    # Push with authentication
    Write-Host "Pushing code to GitHub..." -ForegroundColor White
    Write-Host "(This may take 1-2 minutes...)" -ForegroundColor Gray
    
    $authUrl = $repoUrl -replace "https://", "https://${username}:${tokenPlain}@"
    git push -u $authUrl main
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "========================================================" -ForegroundColor Green
        Write-Host "   ✓✓✓ SUCCESS! CODE UPLOADED! ✓✓✓" -ForegroundColor Green
        Write-Host "========================================================" -ForegroundColor Green
        Write-Host ""
        Write-Host "Repository: $($response.html_url)" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "NEXT STEPS:" -ForegroundColor Yellow
        Write-Host "1. Visit your repo in browser" -ForegroundColor White
        Write-Host "2. Add topics: hackrf, portapack, firmware, sdr, rf" -ForegroundColor White
        Write-Host "3. Enable Actions (if you want auto-builds)" -ForegroundColor White
        Write-Host "4. Share with the community!" -ForegroundColor White
        Write-Host ""
        Write-Host "🦅 EAGLE-FIRMWARE is now live on GitHub! 🦅" -ForegroundColor Green
        Write-Host ""
        
        # Open browser
        Start-Process $($response.html_url)
        
    } else {
        Write-Host ""
        Write-Host "⚠ Push failed. Try manually:" -ForegroundColor Yellow
        Write-Host "git push -u origin main" -ForegroundColor Gray
    }
    
} catch {
    Write-Host ""
    Write-Host "========================================================" -ForegroundColor Red
    Write-Host "   ERROR" -ForegroundColor Red
    Write-Host "========================================================" -ForegroundColor Red
    Write-Host ""
    Write-Host "Error: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host ""
    
    if ($_.Exception.Message -like "*already exists*") {
        Write-Host "Repository already exists!" -ForegroundColor Yellow
        Write-Host ""
        Write-Host "Options:" -ForegroundColor White
        Write-Host "1. Use a different name" -ForegroundColor Gray
        Write-Host "2. Delete the existing repo first" -ForegroundColor Gray
        Write-Host "3. Push to existing repo:" -ForegroundColor Gray
        Write-Host "   git remote add origin https://github.com/$username/$repoName.git" -ForegroundColor Gray
        Write-Host "   git push -u origin main" -ForegroundColor Gray
    } else {
        Write-Host "MANUAL METHOD:" -ForegroundColor Yellow
        Write-Host "1. Go to: https://github.com/new" -ForegroundColor White
        Write-Host "2. Name: $repoName" -ForegroundColor White
        Write-Host "3. Public, no README" -ForegroundColor White
        Write-Host "4. Create, then run:" -ForegroundColor White
        Write-Host "   git remote add origin https://github.com/$username/$repoName.git" -ForegroundColor Gray
        Write-Host "   git branch -M main" -ForegroundColor Gray
        Write-Host "   git push -u origin main" -ForegroundColor Gray
    }
    Write-Host ""
}

Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
