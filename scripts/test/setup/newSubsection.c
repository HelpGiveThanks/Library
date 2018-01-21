January 12, 2018 14:08:37 Library.fmp12 - newSubsection -1-
test: setup: newSubsection
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (new)” ]
#
#Stop spell check script.
Set Variable [ $$stopTest; Value:1 ]
#
#If there are no subsections, then create a new
#subsection group first and then a test for that
#group. All subsections belong to a group.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newSubsectionGroup (update name change newTestGroup)” ]
Exit Script [ ]
End If
#
#Set variables needed to create new subsection.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $group; Value:testSubsectionTemplate::ksubsectionGroup ]
#
#Copy current item's order number.
Set Variable [ $orderNumber; Value:testSubsectionTemplate::order ]
#
#
#Create new subsection.
New Record/Request
#( a test subsection group field is neccessary because a section
# may have more than one test subsection group, and so trying
# to find a test subsection group using the section key and
# the testSubsection match field would find all groups
# when we need the system to find one group. )
Set Field [ testSubsectionTemplate::ksubsectionGroup; $group ]
#
#Set order number if any.
Set Field [ testSubsectionTemplate::order; $orderNumber ]
#
#This new subsections key is placed in its test
#item key field to create future test items
#belonging in this subsection.
Set Field [ testSubsectionTemplate::ktestItemGroup; testSubsectionTemplate::_LtestSubsection ]
#
#Subsections do not need unique names. Unlike other
#names, the names of subsections if named the same
#will not confuse the system. I don't think it will
#confuse the user either, but I am including steps to
#require a unique name so when locked by creator
#the name can be revereted back to orignal name.
Set Field [ testSubsectionTemplate::name; "subsection_template" & testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::nameSpelling; "subsection_template" & testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::kcreatorNode; TEMP::kdefaultNodePrimary ]
#
#
#
#Set temp variables for next part of script.
#
#The subsection's item list temp fields allow
#users to switch from their current list to
#another list.
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
#Assign section to subsection as each
#subsection must be in at least one section.
Perform Script [ “menuTestSection (update and name change from editSectionFocuses)” ]
If [ Get (FoundCount) = 0 ]
Set Variable [ $layout ]
Go to Layout [ “setupTestSection” (testSection) ]
New Record/Request
Set Field [ testSection::match; "testSection" ]
Set Field [ testSection::tag; "section_template" ]
Set Field [ testSection::tagSpelling; "section_template" ]
Perform Script [ “menuTestSection (update and name change from editSectionFocuses)” ]
End If
Go to Record/Request/Page
[ First ]
Perform Script [ “linkOrUnlinkTestSection (update name change linkTestFocusOrUnlinkTestFocus)” ]
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
