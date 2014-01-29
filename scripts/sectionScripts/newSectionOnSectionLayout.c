sectionScripts: newSectionOnSectionLayout
#
If [ tempSetup::kdefaultNodePrimary = "" ]
#
#When running the create new library script, this script
#is the last script to be called. The two steps disabled
#below used to halt the process and then I would
#manually have to go the backup layout and type in
#the word newLibrary to create the trigger for the start
#added below, the script now does that for me.
// Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
// Halt Script
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "newLibrary" ]
Show Custom Dialog [ Message: "This library is now ready for use. It will close. When users next open it they will be asked if they want to use it as a new empty library or import records from an old Library version into it."; Buttons: “OK” ]
Close Window [ Name: "Tag Menus"; Current ﬁle ]
Close Window [ Name: "Setup"; Current ﬁle ]
Exit Script [ ]
End If
#
#Create new section record.
New Record/Request
Set Field [ ruleSection::ksection; ruleSection::_Lgroup ]
Set Field [ ruleSection::match; "section" ]
Set Field [ ruleSection::aboutSection; "This library is for noting what we learn about _________________, collecting references to it, and testing or collecting samples of ___________________ to improve the quality of our thinking and doing or __________________ quality (if
_________________ is a thing not a person)." ]
Set Field [ ruleSection::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
#Capture the name in case the node is deleted, and
#and the section is not requiring the system to replace
#the current sections creator node, name and all.
Set Field [ ruleSection::CaptionORinuseCheck; TEMP::DEFAULTNodePrimaryName ]
#Capture the creator of the node that created the node
#that created this record. Wow! OK, why? Because
#If we need to recreate this section's creator node
#we will need to know who created its creator node.
Set Field [ ruleSection::kSectionCreatorNodesCreator; nodeLockSection::kRecordCreatorNode ]
Set Field [ ruleSection::name; "Empty Library" ]
Set Field [ ruleSection::nameSpelling; "Empty Library" ]
Go to Field [ ruleSection::name ]
#
#Assign section as default section.
Perform Script [ “setDefaultSection” ]
#
January 28, 平成26 17:28:09 Empty Library.fp7 - newSectionOnSectionLayout -1-
