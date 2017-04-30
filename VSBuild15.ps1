get-host

$projects = @("Praktikum_1", "Praktikum_2")
$working_directory = Get-Location

Write-Host "Create project files for Visual Studio 15"
Write-Host "Current working directory: $($working_directory)"

cmake --version

if((Test-Path "build") -ne $true)
{
	Write-Host "Create build folder"
	new-item -itemtype directory build | Out-Null
}

for ($i=0; $i -lt $projects.length; $i++)
{
	$folder = "build/$($projects[$i])";
	if((Test-Path $folder) -ne $true)
	{
		new-item -itemtype directory $folder | Out-Null
	} 
}

for ($i=0; $i -lt $projects.length; $i++)
{
	$a = "build/$($projects[$i])";
	Set-Location $a
	
	Write-Host "Press enter for build next ..."
	$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
	
	cmake "$working_directory/$($projects[$i])/" -G "Visual Studio 14 2015 Win64"
	
    Write-Host "Build $($a)"
	
	Set-Location $working_directory
}

Write-Host "Press any key to continue ..."
$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")