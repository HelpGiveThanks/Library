July 21, 2018 14:18:14 Library.fmp12 - sortOrderNumberPulldownLearnLayouts -1-
tagMenu: sortOrderNumberPulldownLearnLayouts
#
#Exit order number field.
Go to Field [ ]
#
#If in find mode, exit this script.
If [ $$findMode = 1 ]
Exit Script [ ]
End If
#
#If in find mode, exit this script.
If [ $$orderNumbersNotAllowed = 1 ]
Show Custom Dialog [ Message: "Sorry, order numbers are allowed only when brainstorm and test tags are selected in the Tag
Menus window. When time permits this pulldown will be made inaccessable when you cannot use it, for now it is just
hidden."; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$orderNumbersNotAllowed ]
Exit Script [ ]
End If
#
#Decided to allow user to sort by numbers, but
#because a number header adds too much
#distraction, the inventory views do not show it.
// If [ TEMP::InventoryLibraryYN ≠ "" ]
// Show Custom Dialog [ Message: "Inventory records are organized by location, and then alphabetically."; Default Button: “OK”,
Commit: “Yes” ]
// Exit Script [ ]
// End If
#
#Get order number user has selected.
If [ Right ( Get (LayoutName) ; 4 ) = "info" ]
Set Variable [ $order; Value:testlearnReportTags::orderTestInformation ]
Else
Set Variable [ $order; Value:testlearn::orderTestInformation ]
End If
#
#If record is not part of a brainstorm or test exit script.
If [ $$citationMatch = "brainstorm" and testlearn::kcbrainstorm = "" ]
Set Field [ testlearn::orderTestInformation; "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the selected
brainstorm in the Tag Menus window."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the selected
inventory list in the Tag Menus window."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
Else If [ $$citationMatch = "test" and testlearn::kctestSubsectionInfo = "" and Right ( Get (LayoutName) ; 4 ) ≠ "info" ]
Set Field [ testlearn::orderTestInformation; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of a test by clicking any
square button in the Tag Menus window next to a test tag."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#The order number is the left three digits of a
#brainstorm or test record lock number. ( Remember
#each record in the database has lock number or
#ID number. To open the lock and see any record's
#contents requires a key number that fits the lock.
#So if a lock number is 123, then the key that will
#fit this lock is 123 too. ) Because the brainstorm
#and test key fields (think of key chains) may
#have several keys, because any one learn record
#may be part of more than one brainstorm or test.
#the system must check each learn record's keys
#one at a time to see if any fit the current brainstorm
#or test's lock. So beginning with number one
#the system checks each key. The left most 3 numbers
#are order numbers so below you will note that
#they system starts the check on the 4th number
#from the left.
# Once the key whose order number has
#been changed, the old order number is
#replaced with the new one.
Set Variable [ $number; Value:1 ]
If [ $$citationMatch = "brainstorm" ]
Loop
If [ Middle ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 4 ; 42 ) & "¶" = $$tagBrainstorm & ¶ ]
Set Variable [ $replacementValue; Value:Replace ( GetValue ( testlearn::kcbrainstorm ; $number ) ; 1 ; 3 ; $order ) ]
#
#When and if a key is found that fits the current
#brainstorm or test record's lock, the order number
#the user has selected overwrites the left most
#3 digits which by default are 999.
Set Field [ testlearn::kcbrainstorm; Substitute ( $$brainstorm ; GetValue ( testlearn::kcbrainstorm ; $number ) & "¶" ;
$replacementValue & ¶) ]
#
#The 'brainstorm' variable is resset to reflect this change
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$citationItem ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the key having been found.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit the script if the current record is not part
#of the selected brainstorm or test after checking
#all of its keys.
If [ GetValue ( testlearn::kcbrainstorm ; $number ) = "" ]
Set Field [ testlearn::orderTestInformation; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the selected
brainstorm by clicking the square button in the Tag Menus window next to it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Add 1 to the 'number' varaible after each key
#in the key field is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
Else If [ $$citationMatch = "test" ]
If [ Right ( Get (LayoutName) ; 4 ) = "info" ]
Loop
If [ Middle ( GetValue ( testlearnReportTags::kctestSubsectionInfo ; $number ) ; 4 ; 42 ) & "¶" = $$testSubsection & ¶ ]
Set Variable [ $replacementValue; Value:Replace ( GetValue ( testlearnReportTags::kctestSubsectionInfo ;
$number ) ; 1 ; 3 ; $order ) ]
#
#When and if a key is found that fits the current
#brainstorm or test record's lock, the order number
#the user has selected overwrites the left most
#3 digits which by default are 999.
Set Field [ testlearnReportTags::kctestSubsectionInfo; Substitute ( $$test ; GetValue ( testlearnReportTags::
kctestSubsectionInfo ; $number ) & "¶" ; $replacementValue & ¶) ]
#
#The 'test' variable is reset to reflect this change
Set Variable [ $$test; Value:testlearnReportTags::kctestSubsectionInfo ]
Set Variable [ $$citationItem ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the key having been found.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Add 1 to the 'number' varaible after each key
#in the key field is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Else
Loop
If [ Middle ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 4 ; 42 ) & "¶" = $$tagtest & ¶ ]
Set Variable [ $replacementValue; Value:Replace ( GetValue ( testlearn::kctestSubsectionInfo ; $number ) ; 1 ; 3 ;
$order ) ]
#
#When and if a key is found that fits the current
#brainstorm or test record's lock, the order number
#the user has selected overwrites the left most
#3 digits which by default are 999.
Set Field [ testlearn::kctestSubsectionInfo; Substitute ( $$test ; GetValue ( testlearn::kctestSubsectionInfo ;
$number ) & "¶" ; $replacementValue & ¶) ]
#
#The 'test' variable is resset to reflect this change
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$citationItem ]
#
#The 'number' variable is made blank to trigger
#the exit from this loop, the key having been found.
Set Variable [ $number ]
End If
Exit Loop If [ $number = "" ]
#
#Exit the script if the current record is not part
#of the selected brainstorm or test after checking
#all of its keys.
If [ GetValue ( testlearn::kctestSubsectionInfo ; $number ) = "" ]
Set Field [ testlearn::orderTestInformation; "" ]
Show Custom Dialog [ Message: "You can apply an order number to this record when you make it part of the
selected test by clicking the square button in the Tag Menus window next to it."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#Add 1 to the 'number' varaible after each key
#in the key field is checked, to direct the system
#to check the next key.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
End If
End If
#
#Sort the records by order field.
If [ Right ( Get (LayoutName) ; 4 ) = "info" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestInformation; based on value
list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryList; based on value list:
“testPulldownListANDsortOrderList”
testlearn::orderTestInformation; based on value list: “testPulldownListANDsortOrderList”
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#User might have been looking at records
#sorted by date. Now that they are being
#sorted by number, inform the library that this
#is the new view so that when the user clicks
#the sort button again it will switch to the date
#sort view, instead of remaining on the number
#sort view (which is already on).
Set Field [ TEMP::TLBrainstormSort; 1 ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryList; based on value list:
“testPulldownListANDsortOrderList”
testlearn::orderInventoryGroupNumber; ascending
testlearn::orderTestInformation; based on value list: “testPulldownListANDsortOrderList”
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
End If
#
#
#Stop TgotoCitationMenu script.
Set Variable [ $$stopTgotoCitationMenu; Value:1 ]
#
