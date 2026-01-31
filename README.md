# The Metin2 Client
The Old Metin2 Project aims at improving and maintaining the 2014 Metin2 game files up to modern standards. The goal is to archive the game as it was in order to preserve it for the future and enable nostalgic players to have a good time.

For-profit usage of this material is certainly illegal without the proper licensing agreements and is hereby discouraged (not legal advice). Even so, the nature of this project is HIGHLY EXPERIMENTAL - bugs are to be expected for now.

## Description
This is the corresponding client for the Metin2 Server, taken straight out of the "kraizy" leak,
while using files from [TMP4's project](https://metin2.dev/topic/27610-40250-reference-serverfile-client-src-15-available-languages/).

Except for some work in order to ensure compatibility with the server, this client is pretty much
unchanged.

## Requirements

### Installing DirectX 9.0c
The client has been updated to DirectX 9. This means that if DirectX 9 is not installed on your computer, you might be met with one of these error messages:

![picture](/doc/img/directx-error-1.png)
![picture](/doc/img/directx-error-2.png)

In this case, simply [download the DirectX End-User Runtimes (June 2010) from Microsoft's website](http://download.microsoft.com/download/8/4/A/84A35BF1-DAFE-4AE8-82AF-AD2AE20B6B14/directx_Jun2010_redist.exe) (SHA-1 checksum: `7E5D2E5E1A13FBC47F990CC55CBDB428CD12F759`). This is a self-extracting archive, so simply create a new folder, run the executable and extract its contents to that folder.

In this working folder, find and run `DXSETUP.exe` in order to start the install.

After the installation is complete, your client should run without issue.
