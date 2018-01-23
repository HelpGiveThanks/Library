January 12, 2018 14:07:14 Library.fmp12 - newSubsectionGroup -1-
test: setup: newSubsectionGroup
#
#This script is creates test subsection groups.
#
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Stop spell check script.
Set Variable [ $$stopTest; Value:1 ]
#
#Copy current group's order number.
Set Variable [ $orderNumber; Value:testSubsectionGroup::orderOrLibraryType ]
#
#Create new general inquiry group.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; $orderNumber ]
Set Field [ testSubsectionGroup::match; "testSubsection" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
#
#Each group must have a unique name and
#the nameSpelling field is used when the user
#changes the name to a name already in use at
#which point the nameSpelling name can revert
#the user back to the former name (as the name
#field contains the duplicate name which is not
#allowed).
Set Field [ testSubsectionGroup::name; "subsection_group" & testSubsectionGroup::_Lgroup ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "subsection_group" & testSubsectionGroup::_Lgroup ]
Set Variable [ $group; Value:testSubsectionGroup::_Lgroup ]
#
#Create new general inquiry for this group.
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “setupTestSubsection” (testSubsectionTemplate) ]
New Record/Request
Set Variable [ $loopToNewRecord; Value:testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::ksubsectionGroup; $group ]
#
#A new test-item list is created with each new test.
#This key field can be changed so that the test-item
#list for another test can be used.
Set Field [ testSubsectionTemplate::ktestItemGroup; testSubsectionTemplate::_LtestSubsection ]
#
#Tests do not need unique names. Unlike other
#names, the names of tests if named the same
#will not confuse the system. I don't think it will
#confuse the user either, but I am including steps to
#require a unique name so when locked name can
#be revereted back to orignal name.
Set Field [ testSubsectionTemplate::name; "subsection_template" & testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::nameSpelling; "subsection_template" & testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::kcreatorNode; TEMP::kdefaultNodePrimary ]
#
#
#
#Set temp variables for next part of script.
#
#The test item list temp fields allow users to switch
#from their current list to another list.
Set Field [ TEMP::ktestItemSubsection; testSubsectionTemplate::ktestItemGroup ]
Set Field [ TEMP::ktestItemSubsectionOLD; testSubsectionTemplate::ktestItemGroup ]
#
#Used on tag menus to unlock buttons and link
#new records to test.
Set Field [ TEMP::ktestSubsection; testSubsectionTemplate::_LtestSubsection ]
#
#Used on Tag Menus window item layout for switch.
Set Field [ TEMP::testSubsectionName; testSubsectionTemplate::name ]
#
#Used on Tag Menus window section layout for conditional
#formatting.
Set Variable [ $$subsectionSections; Value:testSubsectionTemplate::kcsections ]
#
#
#Go to the tag menus window.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2; Style:
Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “setupTestSection” (testSection) ]
End If
#
#Remember layout user is currently seeing in
#the tag menu window, so user can be returned
#to it at the end of the script.
Set Variable [ $layout; Value:Get (LayoutName) ]
#
#Assign section to test item as each test must have
#at least one section.
Perform Script [ “menuTestSection” ]
If [ Get (FoundCount) = 0 ]
Set Variable [ $layout ]
Go to Layout [ “setupTestSection” (testSection) ]
New Record/Request
Set Field [ testSection::match; "testSection" ]
Set Field [ testSection::tag; "test-section_template" ]
Set Field [ testSection::tagSpelling; "test-section_template" ]
Perform Script [ “menuTestSection” ]
End If
Go to Record/Request/Page
[ First ]
Perform Script [ “linkOrUnlinkTestSection” ]
#
#Go to selected tag menu window layout.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stopLoadTagRecord ]
Go to Layout [ $layout ]
#
#Set variables for new record.
Select Window [ Name: "Test Templates"; Current file ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
#
#Sort records.
Scroll Window
[ Home ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
testSubsectionTemplate::order; based on value list: “order Pulldown List”
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
Go to Field [ testSubsectionTemplate::name ]
[ Select/perform ]
#
#Start spell check script.
Set Variable [ $$stopTest ]
#
