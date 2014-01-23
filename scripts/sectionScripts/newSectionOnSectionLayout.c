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
Set Field [ ruleSection::aboutSection; "I will use this library section to make static memories of my thoughts about and experiences of _________________ to help me remember them and to also analyze, test, and so improve my critical thinking about _________________ ." ]
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
Set Field [ ruleSection::name; "section " & ruleSection::_Lgroup ]
Set Field [ ruleSection::nameSpelling; "section " & groupTest::_Lgroup ]
Go to Field [ ruleSection::name ]
#
#Assign section as default section.
Perform Script [ “setDefaultSection” ]
#
January 7, 平成26 12:13:17 Imagination Quality Management.fp7 - newSectionOnSectionLayout -1-
