///////////////////////////////////////////////////////////////////////
//
//	TOOL.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __TOOL_H__
#define __TOOL_H__

///////////////////////////////////////////////////////////////////////
// ToolType enumeration
typedef enum {
    UnknownTool,
    NoteTool,
    ModifierTool
} ToolType;

///////////////////////////////////////////////////////////////////////
typedef struct {
    ToolType type;          // tool type
	UINT button;            // button identifier
    UINT icon;              // icon identifier
    UINT cursor;            // cursor identifier
	LONG user;				// custom data
} Tool;
///////////////////////////////////////////////////////////////////////

// The Tool structure contains a user defined member named
// user of type LONG.  Depending on the ToolType member of the structure
// this data member has different meanings.  The following table
// outlines the meaning of this member as it pertains to different
// types of Tools:
//
//  type            user
//  --------        ----
//  UnknownTool     ???
//  NoteTool        represents a Duration enumeration, describing
//                  the duration of the note.
//  ModifierTool    represents a Modifier enumeration to the note to which it will modify
//
 
#endif // __TOOL_H__
