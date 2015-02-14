testScreens: testReport: InUsePart3
#
// #Determine if record is a discovery or info record.
// #This information will be used by other parts of
// #this script to figure out which Tag Menu layout
// #to go to when neccessary: discover or info.
// If [ ]
// End If
#
#BEGIN A
#[by David Matson 4.18.11, last modified by ]
#If user has selected to copy a finding from the Report window
#to remove it or to move it to another slot...
If [ Get ( ActiveFieldName ) = "_kfPhoto" and $$finding = "" or
Get ( ActiveFieldName ) = "_kfPhoto2" and $$finding = "" or
Get ( ActiveFieldName ) = "_kfPhoto3" and $$finding = "" or
Get ( ActiveFieldName ) = "_kfPhoto4" and $$finding = "" ]
#
#
#
#BEGIN a1
#[by David Matson 4.18.11, last modified by ]
#If user is trying to copy blank field
#stop the script
If [ $$finding = "" and Get (ActiveFieldContents) = "" ]
Go to Field [ ]
Halt Script
End If
#[validated by David Matson 4.18.11]
#END a1
#
#
#
#copy it
Set Variable [ $$finding; Value:Get ( ActiveFieldContents ) ]
Set Variable [ $$window; Value:"Report" ]
Refresh Window
Clear [ ]
[ Select ]
Go to Field [ ]
#
#Inform user of where tag is now located by changing
#conditional formatting: green = in use,
#yellow = reaady to paste, normal colors = not
#use and not copied for pasting.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LayoutName) ≠ "reportTagDiscovery" ]
Perform Script [ “reportTagDiscovery” ]
End If
Go to Field [ ]
#
#find the record that has been copied and cleared
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If it is not a discovery record, go to the info layout.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Perform Script [ “reportTagInfo” ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
End If
#
#inform the user that it is not being used in the Report window
#by removing it from the list of inUse report sections,
#basically removing it from showing on this page but
#not the other pages it is currently being used by.
Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
Set Field [ testlearnReportTags::inUse; Substitute ( testlearnReportTags::inUse ; $$contact & $$reportNumber & "¶" ; "" ) ]
#
Select Window [ Name: "Report"; Current file ]
Halt Script
#[validated by David Matson 4.18.11]
#END A
#
#
#
#BEGIN B
#[by David Matson 4.18.11, last modified by ]
#
#If user has selected to put a copied finding from the Report window,
#into a blank slot,
Else If [ Get ( ActiveFieldName ) = "_kfPhoto" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "_kfPhoto2" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "_kfPhoto3" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "_kfPhoto4" and Get ( ActiveFieldContents )="" and $$finding ≠ "" and $$window = "Report" ]
#paste ID in blank slot
Set Field [ $$finding ]
Go to Field [ ]
#
#Inform user of where tag is now located by changing
#conditional formatting: green = in use,
#yellow = reaady to paste, normal colors = not
#use and not copied for pasting.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LayoutName) ≠ "reportTagDiscovery" ]
Perform Script [ “reportTagDiscovery” ]
End If
Go to Field [ ]
#
#find the record that has been copied and cleared
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
January 7, 平成26 14:28:27 Imagination Quality Management.fp7 - InUsePart3__DavidMatsonALLValid4.18.11 -1-testScreens: testReport: InUsePart3__DavidMatsonALLValid4.18.11
#
#If it is not a discovery record, go to the info layout.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Perform Script [ “reportTagInfo” ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
End If
#
#inform the user that it is being used in the Report window
#by adding it to the list of report sections where it is used.
#This will increase the used: # by one.
Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
Set Field [ testlearnReportTags::inUse; $inUse & $$contact & $$reportNumber & "¶" ]
#
#clear the $$finding and $window variables
Set Variable [ $$finding ]
Set Variable [ $$window ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
Halt Script
#[validated by David Matson 4.18.11]
#END B
#
#
#
#BEGIN C
#[by David Matson 4.18.11, last modified by ]
#
#If user has selected to insert a copied finding from the Report window,
#into a slot already occupied,
#PREVENT USER FROM DOING SO. DISABLE PART C.
Else If [ Get ( ActiveFieldName ) = "_kfPhoto" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "_kfPhoto2" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
or
Get ( ActiveFieldName ) = "_kfPhoto3" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Report"
 or
Get ( ActiveFieldName ) = "_kfPhoto4" and Get ( ActiveFieldContents ) ≠ ""and $$window = "Report" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Click the X button to clear this slot before pasting anything into it. If you want to copy this item, then 1) click on any green empty slot, 2) re-click on the item want to copy."; Buttons: “OK” ]
Exit Script [ ]
// #copy the occupying records ID
// Set Variable [ $ID; Value:Get ( ActiveFieldContents ) ]
// #paste in the desired records ID in its place (contact and thing IDs are already there)
// Set Field [ $$finding ]
// Go to Field [ ]
// #now go to the Inspection Findings window, note the record the user is on
// Select Window [ Name: "Tag Menus"; Current file ]
// Set Variable [ $record; Value:Get ( RecordNumber ) ]
// Go to Field [ ]
// #
// #open new window so as to avoid scroll issue
// New Window [ ]
// #
// #find the record that has been replaced and thus removed from the Report window
// Enter Find Mode [ ]
// Set Field [ testlearnReportTags::_Ltestlearn; $ID ]
// Perform Find [ ]
// #inform the user that it is not being used in the Report window
// #by removing it from the list of inUse report sections,
// #basically removing it from showing on this page but
// #not the other pages it is currently being used by.
// Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
// Set Field [ testlearnReportTags::inUse; Substitute ( testlearnReportTags::inUse ; $$contact & $$reportNumber & "¶" ; "" ) ]
// Set Variable [ $ID ]
// #find the record that has been inserted
// Enter Find Mode [ ]
// Set Field [ testlearnReportTags::_Ltestlearn; $$finding ]
// Perform Find [ ]
// #inform the user that it is being used in the Report window
// #by adding it to the list of report sections where it is used
// Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
// Set Field [ testlearnReportTags::inUse; testlearnReportTags::inUse & $$contact & $$reportNumber & "¶" ]
// #
// #finally, re-find the records the user was looking at, and go to specific record the user was on.
// Set Variable [ $contact; Value:testlearnReportTags::ktestSubject ]
// Set Variable [ $item; Value:testlearnReportTags::ktest ]
// Enter Find Mode [ ]
// Set Field [ testlearnReportTags::ktestSubject; $contact ]
// Set Field [ testlearnReportTags::ktest; $item ]
// Set Field [ testlearnReportTags::kreportNumber; $$reportNumber ]
// Perform Find [ ]
// If [ TEMP::showFavorites ≠ "" ]
// Set Field [ TEMP::showFavorites; "" ]
// Perform Script [ “<unknown>” ]
// Else If [ TEMP::showFavorites = "" ]
// Sort Records [ Specified Sort Order: testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page [ $record ]
[ No dialog ]
// End If
// #clear the $$finding and $window variables
// Set Variable [ $$finding ]
// Set Variable [ $$window ]
// Close Window [ Current Window ]
// Halt Script
// #[validated by David Matson 4.18.11]
// #END C
#
#
#
#BEGIN D
#[by David Matson 4.18.11, last modified by ]
#If user has selected to insert a finding from the finding window
#into an occupied slot on the Report window
#PREVENT USER FROM DOING SO. DISABLE PART C.
Else If [ Get ( ActiveFieldName ) = "_kfPhoto" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
 or
Get ( ActiveFieldName ) = "_kfPhoto2" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
or
Get ( ActiveFieldName ) = "_kfPhoto3" and Get ( ActiveFieldContents ) ≠ "" and $$window = "Tag Menus"
 or
Get ( ActiveFieldName ) = "_kfPhoto4" and Get ( ActiveFieldContents ) ≠ ""and $$window = "Tag Menus" ]
January 7, 平成26 14:28:27 Imagination Quality Management.fp7 - InUsePart3__DavidMatsonALLValid4.18.11 -2-testScreens: testReport: InUsePart3__DavidMatsonALLValid4.18.11
Go to Field [ ]
Show Custom Dialog [ Message: "Click the X button to clear this slot before pasting anything into it. If you want to copy this item, then 1) click on any green empty slot, 2) re-click on the item want to copy."; Buttons: “OK” ]
Exit Script [ ]
// #
// #
// #
// #BEGIN d1
// #[by David Matson 4.18.11, last modified by ]
// #If user is trying to copy the same finding into the location it currently occupies
// #stop the script
// Set Variable [ $ID; Value:Get ( ActiveFieldContents ) ]
// If [ $$finding = $ID ]
// Go to Field [ ]
// Set Variable [ $$finding ]
// Halt Script
// End If
// #[validated by David Matson 4.18.11]
// #END d1
// #
// #
// #
// #paste in the desired records ID in its place (contact and thing IDs are already there)
// Set Field [ $$finding ]
// Go to Field [ ]
// #tell user it is now in use
// #by adding it to the list of report sections where it is used
// Select Window [ Name: "Tag Menus"; Current file ]
// Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
// Set Field [ testlearnReportTags::inUse; testlearnReportTags::inUse & $$contact & $$reportNumber & "¶" ]
// #clear the $$finding variable
// Set Variable [ $$finding ]
// Set Variable [ $$window ]
// #note the record the user is on
// Select Window [ Name: "Tag Menus"; Current file ]
// Set Variable [ $record; Value:Get ( RecordNumber ) ]
// Go to Field [ ]
// #
// #open new window so as to avoid scroll issue
// New Window [ ]
// #
// #find the record that has been replaced and thus removed from the Report window
// Enter Find Mode [ ]
// Set Field [ testlearnReportTags::_Ltestlearn; $ID ]
// Perform Find [ ]
// #inform the user that it is not being used in the Report window
// #by removing it from the list of inUse report sections,
// #basically removing it from showing on this page but
// #not the other pages it is currently being used by.
// Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
// Set Field [ testlearnReportTags::inUse; Substitute ( testlearnReportTags::inUse ; $$contact & $$reportNumber & "¶" ; "" ) ]
// Set Variable [ $ID ]
// #
// #finally, re-find the records the user was looking at, and go to specific record the user was on.
// Set Variable [ $contact; Value:testlearnReportTags::ktestSubject ]
// Set Variable [ $item; Value:testlearnReportTags::ktest ]
// Enter Find Mode [ ]
// Set Field [ testlearnReportTags::ktestSubject; $contact ]
// Set Field [ testlearnReportTags::ktest; $item ]
// Set Field [ testlearnReportTags::kreportNumber; $$reportNumber ]
// Perform Find [ ]
// If [ TEMP::showFavorites ≠ "" ]
// Set Field [ TEMP::showFavorites; "" ]
// Perform Script [ “<unknown>” ]
// Else If [ TEMP::showFavorites = "" ]
// Sort Records [ Specified Sort Order: testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page [ $record ]
[ No dialog ]
// End If
// Close Window [ Current Window ]
// Go to Field [ ]
// Halt Script
End If
#END D
#[validated by David Matson 4.18.11]
#
#
#
#BEGIN E
#[by David Matson 4.16.11, last modified by same 4.18.11]
#If user has selected to copy of a finding from the finding window
#into a blank slot on the report window, put it in there
Set Field [ $$finding ]
Go to Field [ ]
#
#Inform user of where tag is now located by changing
#conditional formatting: green = in use,
#yellow = reaady to paste, normal colors = not
#use and not copied for pasting.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LayoutName) ≠ "reportTagDiscovery" ]
Perform Script [ “reportTagDiscovery” ]
End If
Go to Field [ ]
#
#find the record that has been copied and cleared
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If it is not a discovery record, go to the info layout.
If [ $$finding ≠ testlearnReportTags::_Ltestlearn ]
Perform Script [ “reportTagInfo” ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Loop
Exit Loop If [ $$finding = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
End If
#
January 7, 平成26 14:28:27 Imagination Quality Management.fp7 - InUsePart3__DavidMatsonALLValid4.18.11 -3-testScreens: testReport: InUsePart3__DavidMatsonALLValid4.18.11
#inform the user that it is being used in the Report window
#by adding it to the list of report sections where it is used.
#This will increase the used: # by one.
Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
Set Field [ testlearnReportTags::inUse; $inUse & $$contact & $$reportNumber & "¶" ]
#
#clear the $$finding and $window variables
Set Variable [ $$finding ]
Set Variable [ $$window ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
#
#END E
#[validated by David Matson 4.18.11]
January 7, 平成26 14:28:27 Imagination Quality Management.fp7 - InUsePart3__DavidMatsonALLValid4.18.11 -4-
