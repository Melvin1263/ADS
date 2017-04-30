#get-host

$build_path = "build/"
$cmake_cmd = "cmake"
$projects = @("Praktikum_1", "Praktikum_2")
$working_directory = Get-Location

Write-Host "Create project files for Visual Studio 14 2015"
Write-Host "Current working directory: $($working_directory)"

Write-Host "Check for cmake"
if([bool](Get-Command -name $cmake_cmd) -ne $true)
{
	Write-Host "Press any key to exit ..."
	$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
	exit
}

&$cmake_cmd --version

if((Test-Path $build_path) -ne $true)
{
	Write-Host "Create build folder"
	new-item -itemtype directory build | Out-Null
}

for ($i=0; $i -lt $projects.length; $i++)
{
	$folder = "$($build_path)$($projects[$i])";
	if((Test-Path $folder) -ne $true)
	{
		new-item -itemtype directory $folder | Out-Null
	} 
}

for ($i=0; $i -lt $projects.length; $i++)
{
	$folder = "$($build_path)$($projects[$i])";
	Set-Location $folder
	
	Write-Host "Want to build $($folder)"
	Write-Host "Press enter for build ..."
	$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
	
	&$cmake_cmd "$working_directory/$($projects[$i])/" -G "Visual Studio 14 2015 Win64"
	
    Write-Host "Build $($folder)"
	
	Set-Location $working_directory
}

Write-Host "Press any key to exit ..."
$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")