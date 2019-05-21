# Lightweight Firestore C++

This repository features a simple firestore class that uses gRPC for communication.

## Build

The project includes a Firestore.sln file that can be compiled with Visual Studio.

To set up the dependencies, use the following vcpkg command:

.\vcpkg install google-cloud-cpp:x64-windows-v140

(we have used a custom x64-windows-v140 triplet, however you can select any triplet of your choice.)

This will download and compile gRPC, OpenSSL, and other dependencies we need.

Make sure that the global properties in the Firestore.vcxproj and Tests/Tests.vcxproj files match
the triplet you used when installing the dependencies:

<PropertyGroup Label="Globals">
    ...
    <VcpkgTriplet>x64-windows-v140</VcpkgTriplet> // enter your triplet here
</PropertyGroup>

Then, add the following environment variables:

- VCPKG_ROOT=Root folder containing vcpkg.exe
- GOOGLE_APPLICATION_CREDENTIALS=[PATH_TO_CREDENTIALS]
- - See https://cloud.google.com/docs/authentication/getting-started for more information
- GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=[VCPCK_ROOT]\installed\x64-windows-v140\share\grpc

Now Firestore should compile, and you should be able to run the Tests project.

### Custom VCPKG triplet for toolset v140

To install google-cloud-cpp for toolset v140 when toolset v141 is installed,
create a copy of:
vcpkg/triplets/x64-windows.cmake

And name it:
x64-windows-v140.cmake

(Note: doing this with x64-windows.cmake instead produced an error)

Then open the file and add the following line:
set(VCPKG_PLATFORM_TOOLSET v140)

Then run the followin command to install:
.\vcpkg.exe install google-cloud-cpp:x64-windows-v140

Then (for visual studio) open the .vcxproj file and find and add:
<PropertyGroup Label="Globals">
    ...
    <VcpkgTriplet>x64-windows-v140</VcpkgTriplet> // added
</PropertyGroup>

Note that the vcpkg packages may not be included automatically.
In that case, you have to manually add them to the project.