tagMenu: defaultTestLocationMenu
#
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button."; Buttons: “OK” ]
Halt Script
Else If [ tempSetup::kdefaultHealth = "" ]
Show Custom Dialog [ Message: "Select the default copyright for any new records that you create by clicking the copyright button (you can always change your mind)."; Buttons: “OK” ]
Halt Script
End If
#
#A section must be selected before locations
#can be assigned.
If [ TEMP::ksection = "" ]
Perform Script [ “defaultSectionMenu” ]
Show Custom Dialog [ Message: "You must select a section prior to clicking the 'test' button. All tests belong to specific sections. "; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Make sure creator node's group is part of section group.
Perform Script [ “addBackSectionCreatorNode” ]
// #
// #A test subject must be selected before locations
// #be assigned.
// If [ tempSetup::kdefaultNodeTestSubject = "" ]
// Show Custom Dialog [ Message: "Select a test subject."; Buttons: “OK” ]
// Perform Script [ “defaultNodeMenu” ]
// Exit Script [ ]
// End If
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"location" ]
#
#Locations are shown are the general locations
#for a test. This menu will be used to create
#specific locations for a specific test subject.
#So in the Setup window the system highlights
#the test subject for whom the locations are going
#to be created.
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Find all test location records.
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
// Set Field [ tagTestSubjectLocation::knode; TEMP::kdefaultNodeTestSubject ]
Set Field [ tagTestSubjectLocation::ksection; TEMP::ksection ]
Perform Find [ ]
#
#Sort
Sort Records [ Specified Sort Order: tagTestSubject::tag; ascending
tagTestSubjectLocation::reportNumber; ascending
tagTestSubjectLocation::order; based on value list: “order”
tagTestSubjectLocation::focusName; ascending ]
[ Restore; No dialog ]
#
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "Setup"; Current file ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Clear current temp field of location names in
#case user has selected a section different from
#the one previous, and thus with name that might
#not match those in these temp fields.
Set Field [ TEMP::LocationName; "" ]
Set Field [ TEMP::modifier1name; "" ]
Set Field [ TEMP::modifier2name; "" ]
Set Field [ TEMP::kfocus; "" ]
Set Field [ TEMP::kmodifier1; "" ]
Set Field [ TEMP::kmodifier2; "" ]
Set Field [ TEMP::orderLocation; "" ]
Set Field [ TEMP::orderMod1; "" ]
Set Field [ TEMP::orderMod2; "" ]
#
#Set reportnumber to a default of 1.
Set Field [ TEMP::reportNumber; 1 ]
#
#Set temp keys to unlock pulldown lists for
#section locations.
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::ksection; TEMP::ksection ]
Set Field [ groupTest::match; "location" ]
Perform Find [ ]
Set Field [ TEMP::locationSection; groupTest::_Lgroup ]
#
#Set temp keys to unlock pulldown lists for
#section attributes.
Enter Find Mode [ ]
Set Field [ groupTest::ksection; TEMP::ksection ]
Set Field [ groupTest::match; "attribute" ]
Perform Find [ ]
Set Field [ TEMP::pulldownAttribute; groupTest::_Lgroup ]
#
#Return to tag menu layout.
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
January 28, 平成26 15:52:43 Empty Library copy.fp7 - defaultTestLocationMenu -1-
