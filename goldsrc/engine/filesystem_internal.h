/*
 *	This file is part of OGS Engine
 *	Copyright (C) 2018 BlackPhrase
 *
 *	OGS Engine is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	OGS Engine is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OGS Engine. If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// @brief internal filesystem module wrapper

#pragma once

#define FILESYSTEM_INTERNAL_H

#define FILESYSTEM_INVALID_HANDLE (FileHandle_t)0

typedef enum
{
	FILESYSTEM_SEEK_HEAD = 0,
	FILESYSTEM_SEEK_CURRENT,
	FILESYSTEM_SEEK_TAIL
	//...?
} FileSystemSeek_t;

enum
{
	FILESYSTEM_INVALID_FIND_HANDLE = -1
};

typedef enum
{
	FILESYSTEM_WARNING_QUIET = 0,      ///< Don't print anything
	FILESYSTEM_WARNING_REPORTUNCLOSED, ///< On shutdown, report names of files left unclosed
	FILESYSTEM_WARNING_REPORTUSAGE,    ///< Report number of times a file was opened/closed
	FILESYSTEM_WARNING_REPORTALLACCESS ///< Report all open/close events to console (SLOW!!!!)
} FileWarningLevel_t;


////////////
// TODO: here or somewhere else?????

void FileSystem_Init(char *basedir, void *filesystemFactory); // TODO: return bool/int?
void FileSystem_Shutdown();
////////////

// VFileSystem009 interface wrapper

//void FS_Mount();
//void FS_Unmount();

void FS_RemoveAllSearchPaths();

void FS_AddSearchPath(const char *pPath, const char *pathID);
bool FS_RemoveSearchPath(const char *pPath);

void FS_RemoveFile(const char *pRelativePath, const char *pathID);

void FS_CreateDirHierarchy(const char *path, const char *pathID);

bool FS_FileExists(const char *pFileName);
bool FS_IsDirectory(const char *pFileName);

FileHandle_t FS_Open(const char *pFileName, const char *pOptions, const char *pathID);
void FS_Close(FileHandle_t file);

void FS_Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType);
unsigned int FS_Tell(FileHandle_t file);

unsigned int FS_Size(FileHandle_t file);
unsigned int FS_Size(const char *pFileName); // TODO: FS_FileSize? C doesn't support function overloading so this won't work otherwise

long FS_GetFileTime(const char *pFileName);
void FS_FileTimeToString(char *pStrip, int maxCharsIncludingTerminator, long fileTime);

bool FS_IsOk(FileHandle_t file);

void FS_Flush(FileHandle_t file);
bool FS_EndOfFile(FileHandle_t file);

int FS_Read(void *pOutput, int size, FileHandle_t file);
int FS_Write(void const *pInput, int size, FileHandle_t file); // void const
char *FS_ReadLine(char *pOutput, int maxChars, FileHandle_t file);
int FS_FPrintf(FileHandle_t file, char *pFormat, ...);

void *FS_GetReadBuffer(FileHandle_t file, int *outBufferSize, bool failIfNotInCache);
void FS_ReleaseReadBuffer(FileHandle_t file, void *readBuffer);

const char *FS_FindFirst(const char *pWildCard, FileFindHandle_t *pHandle, const char *pathID);
const char *FS_FindNext(FileFindHandle_t handle);
bool FS_FindIsDirectory(FileFindHandle_t handle);
void FS_FindClose(FileFindHandle_t handle);

void FS_GetLocalCopy(const char *pFileName);

const char *FS_GetLocalPath(const char *pFileName, char *pLocalPath, int localPathBufferSize);

char *FS_ParseFile(char *pFileBytes, char *pToken, bool *pWasQuoted);

bool FS_FullPathToRelativePath(const char *pFullpath, char *pRelative);

bool FS_GetCurrentDirectory(char *pDirectory, int maxlen);

void FS_PrintOpenedFiles();

void FS_SetWarningFunc(void (*pfnWarning)(const char *fmt, ...));
void FS_SetWarningLevel(FileWarningLevel_t level);

void FS_LogLevelLoadStarted(const char *name);
void FS_LogLevelLoadFinished(const char *name);

int FS_HintResourceNeed(const char *hintlist, int forgetEverything);

int FS_PauseResourcePreloading();
int FS_ResumeResourcePreloading();

int FS_SetVBuf(FileHandle_t stream, char *buffer, int mode, long size);

void FS_GetInterfaceVersion(char *p, int maxlen);

bool FS_IsFileImmediatelyAvailable(const char *pFileName);

WaitForResourcesHandle_t FS_WaitForResources(const char *resourcelist);
bool FS_GetWaitForResourcesProgress(WaitForResourcesHandle_t handle, float *progress, bool *complete);
void FS_CancelWaitForResources(WaitForResourcesHandle_t handle);

bool FS_IsAppReadyForOfflinePlay(int appID);

bool FS_AddPackFile(const char *fullpath, const char *pathID);

FileHandle_t FS_OpenFromCacheForRead(const char *pFileName, const char *pOptions, const char *pathID);

void FS_AddSearchPathNoWrite(const char *pPath, const char *pathID);

////////////

/// returns the file size
/// return -1 if file is not present
/// the file should be in BINARY mode for stupid OSs that care
int FS_FileOpenRead(const char *path, int *hndl);

int FS_FileOpenWrite(const char *path);

void FS_FileClose(int handle);

void FS_FileSeek(int handle, int position);

int FS_FileRead(int handle, void *dest, int count);
int FS_FileWrite(int handle, const void *data, int count);

int	FS_FileTime(const char *path);

void FS_mkdir(const char *path);

// Dynamic Library Management
	
//void *FS_LoadLibrary(const char *name, const char *path);