#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#pragma once

#ifdef NTDDI_VERSION
#include <ntddk.h>
#else

#endif 

#define NOTIFICATION_STRING_BUFFER_SIZE 1000


#define NOTIFICATION_REGISTRY_OPEN_KEY 1
#define NOTIFICATION_REGISTRY_CREATE_KEY 2
#define NOTIFICATION_REGISTRY_ENUMERATE_SUBKEYS 3
#define NOTIFICATION_REGISTRY_SET_VALUE 4
#define NOTIFICATION_REGISTRY_QUERY_VALUE 5

typedef struct _OBSERVER_NOTIFICATION {
	UINT32	NotificationType;
	UINT32	Reaction;
	UINT64	CurrentProcessID;
	UINT64	CurrentThreadID;
	union
	{
		struct
		{
			UINT16	RegistryAction;
			UINT16	Truncated;
			WCHAR	ValueName[64];
			WCHAR	KeyPath[NOTIFICATION_STRING_BUFFER_SIZE];
		} Registry;
		struct
		{
			UINT64  NewThreadID;
			UINT64  TargetProcessID;
		} ThreadCreated;
		struct
		{
			UINT64  NewProcessID;
			UINT64  ParentProcessID;
			UINT64  CreatingThreadID;
			UINT64  CreatingProcessID;
			UINT16	Truncated;
			WCHAR	ImageNamePath[NOTIFICATION_STRING_BUFFER_SIZE];
		} ProcessCreated;
		struct
		{
			UINT64 TargetProcessID;
			ACCESS_MASK RequestedAccess;
		} ProcessOpened;
		struct
		{
			UINT64	ImageBase;
			UINT64	ImageSize;
			UINT32  ImageSigned		: 1;
			UINT32  SystemImage		: 1;
			UINT32	Reserved		: 30;
			UINT16  Truncated;
			WCHAR	ImageName[NOTIFICATION_STRING_BUFFER_SIZE];
		} ModuleLoaded;
		struct
		{
			UINT64	ImageBase;
			UINT64	ImageSize;
			UINT32  ImageSigned : 1;
			UINT32  SystemImage : 1;
			UINT32	Reserved : 30;
			UINT16  Truncated;
			WCHAR	ImageName[NOTIFICATION_STRING_BUFFER_SIZE];
		} DriverLoaded;
	} Types;
} OBSERVER_NOTIFICATION, *POBSERVER_NOTIFICATION;

#endif // !NOTIFICATION_H
