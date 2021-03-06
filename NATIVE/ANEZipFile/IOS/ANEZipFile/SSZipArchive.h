//
//  SSZipArchive.h
//  SSZipArchive
//
//  Created by Sam Soffes on 7/21/10.
//  Copyright (c) Sam Soffes 2010-2011. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "minizip/unzip.h"

@protocol SSZipArchiveDelegate;

@interface SSZipArchive : NSObject

// Unzip
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error;

+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination delegate:(id<SSZipArchiveDelegate>)delegate;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error delegate:(id<SSZipArchiveDelegate>)delegate;

// Zip
+ (BOOL)createZipFileAtPath:(NSString *)path withFilesAtPaths:(NSArray *)paths andDelegate:(id<SSZipArchiveDelegate>)delegate;
+ (BOOL)createZipFileAtPath:(NSString *)path withFilesAtPaths:(NSArray *)paths atPaths:(NSArray*)atPaths andDelegate:(id<SSZipArchiveDelegate>)delegate;

+ (NSMutableArray*)getFilesInZip:(NSString *)path password:(NSString *)password;
+(NSMutableData*)unzipFileFrom:(NSString*)path withName:(NSString*)fileName password:(NSString*)password;
+ (BOOL)isPasswordProtected:(NSString*)path;

- (id)initWithPath:(NSString *)path;
- (BOOL)open;
- (BOOL)openForAppend;

- (BOOL)writeFile:(NSString *)path;
- (BOOL)writeFileAtPath:(NSString *)path filePath:(NSString*)filePath;
- (BOOL)writeData:(NSData *)data filename:(NSString *)filename;
- (BOOL)close;

@end


@protocol SSZipArchiveDelegate <NSObject>

@optional

- (void)zipArchiveWillUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo;
- (void)zipArchiveDidUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo unzippedPath:(NSString *)unzippedPath;

- (void)zipArchiveWillUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;
- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;

- (void)zipArchiveWillZipArchiveAtPath:(NSString *)path;
- (void)zipArchiveDidZipArchiveAtPath:(NSString *)path withSuccess:(BOOL)success;
- (void)zipArchiveDidProgress:(int)current on:(int)total;

@end
