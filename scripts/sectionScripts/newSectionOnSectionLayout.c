sectionScripts: newSectionOnSectionLayout
#
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
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
January 28, 平成26 16:03:24 Empty Library copy.fp7 - newSectionOnSectionLayout -1-
