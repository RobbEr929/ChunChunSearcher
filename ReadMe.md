## Background About ChunChunSearcher

For graduation design. Desktop file retrieval software based on windows can realize rapid retrieval and monitoring of files.

Using C++ language, based on cpp17, Qt5.12.12, Visual Studio 2019, Microsoft's USN log system, development completed.
## Current version V1.2.0
- Added cloud disk function, cloud disk is divided into personal cloud disk and organizational cloud disk. After logging in, you can upload and download files. The default download path is `installation path/download/username`;
- Added organization function, you can create and join organizations. Organization members have four kinds of permissions, namely `member`, `file administrator`, `member administrator`, and `organization creator` permissions increase in order;
- Added chat room function, one device needs to open the server, other devices can connect to the server through ip to realize the chat function;
- Temporarily update here~
### Version V1.1.0 Update
Added login and registration functions, based on the cloud platform interface, through the `Http` request `RESTful Api` call, the backend uses the `PHPLaravel` framework, and the database is `MySQL`.

## Install

Click `ChunChunSearcher.msi`, install as required.

## Usage

Click `ChunChunSearcher.exe` can be used. The software will request administrator permission. Please give it to continue;

After entering, wait for 5-10S for scanning, and start searching after the status bar in the lower left corner reminds you of the completion of scanning;

The search result list can be **quickly opened, copied path, deleted and viewed properties**;

According to the test, the resident memory of about 100k entries is about 40m, 600k is 100m and 1.8m entries about 300m.

### V1.1.0 Update

Added login and registration functions, and can synchronize settings in the cloud.

### V1.0.1 Update
Update the development environment to VS2022.If the runtime library is not suitable, please contact the author, see [Github homepage](https://github.com/RobbEr929)

## Set

### General settings
You can set background operation, tray display, automatic update and prompt information.

### V1.1.0 Update
Added disable network function, the function is the same as V1.0.0 after disabling.
### Retrieval settings
1. Case matching: when enabled, the strict case will be retrieved;
2. Matching path: when enabled, the file path will be retrieved (**which will significantly slow down the search speed**);
3. Matching file: after opening, the file name will be retrieved;
4. Regular expressions: regular expressions will be supported when enabled.

### Index settings

1. Enable or disable volumes in volume management;
2. The exclusion path can be set to reduce the interference of system files on search results;
3. The monitoring path can be set to update in real time;

### About

Including software information and author information, welcome to reward~

## Maintainers

[@RobbEr's blog](https://robber.ltd)

[@RobbEr's GitHub](https://github.com/RobbEr929)

## License
[MIT](./LICENSE) © Zhong Chun