July 21, 2018 14:15:14 Library.fmp12 - loadTestTags -1-
tagMenu: loadTestTags
#
#Capture recordID to conditionally format current record.
If [ $$stopLoadTagRecord ≠ 1 ]
Go to Field [ ]
#
#The 'test' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagtest; Value:testSubsectionTemplate::_LtestSubsection ]
Set Field [ TEMP::kctagTest; testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $$BrainstormOrTestID; Value:Get (RecordID) ]
#
#The next conditional formatting variable needs
#to be cleared in case there are no records in
#the learn window tagged with this tag record.
#It might contain a tag ID from the selecting
#the previous record which did have at least 1
#learn record tagged with it. (See the end of
#this script where it is actually created.)
Set Variable [ $$atLeastOneRecord ]
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Move/Resize Window [ Current Window; Height: 3; Width: 3; Top: -1000; Left: -1000 ]
Go to Layout [ “learn2” (testlearn) ]
#Prepare system to stop error message about no
#records being found as the user may not have
#yet tagged any learn records with this test tag.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" ]
Perform Find [ ]
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: testlearn::kctestSubsectionInfo: “=” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:1 ]
Loop
Exit Loop If [ Case ( Left ( testlearn::kctestSubsectionInfo ; 2 ) = "00" ;
//If there two zeros in front of the order number, get the key using these calculations:
(FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 1 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 2 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 3 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 4 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 5 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 6 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 7 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 8 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 9 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 10 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
) = 1 ;
//If there is only one zero in front of the order number, get the key using this calculation:
(FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 1 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 2 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 3 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 4 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 5 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 6 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 7 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 8 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 9 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 10 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
) = 1
) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $atLeastOneRecord; Value:Case ( Left ( testlearn::kctestSubsectionInfo ; 2 ) = "00" ;
//If there two zeros in front of the order number, get the key using this calculation:
If ( (FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 1 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 2 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 3 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 4 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 5 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 6 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 7 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 8 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 9 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 10 ) ; 4 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
) = 1 ; 1 ; "" ) ;
//If there is only one zero in front of the order number, get the key using this calculation:
If ( (FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 1 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 2 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 3 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 4 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 5 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 6 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 7 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 8 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 9 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kctestSubsectionInfo ; 10 ) ; 3 ; 42 ) ; $$tagtest & "¶" ) = $$tagtest & ¶
) = 1 ; 1 ; "" )
) ]
Go to Layout [ original layout ]
Close Window [ Current Window ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#This won't work without going through every
#record on the main window to check if it is tagged
#with this record, and that could take a really long
#time.
#So if there are no records tagged with this test item
#then make sure the Main window is sorted by
#date and not by test item sort order.
If [ $atLeastOneRecord ≠ 1 ]
#
#The 'test' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagtest; Value:testSubsectionTemplate::_LtestSubsection ]
#
Select Window [ Name: "Learn"; Current file ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
End If
Scroll Window
[ Home ]
Set Field [ TEMP::TLTestSort; "" ]
Set Variable [ $$stopLoadCitation ]
Perform Script [ “loadLearnOrRefMainRecord” ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
Else If [ $atLeastOneRecord = 1 ]
#
#The formatting of test tagged records in
#the Learn window is linked to the current
#record in the tag window. THE ONLY WAY to
#know this in the Tag window (that there are
#tagged records in the learn window) is to
#make a $$ variable. This way the system will
#remember it is conditionally formatting learn
#records when the active learn record is not
#tagged with the current record in the tag window.
Set Variable [ $$atLeastOneRecord; Value:$$tagtest ]
#
#The 'test' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagtest; Value:testSubsectionTemplate::_LtestSubsection ]
Set Field [ TEMP::kctagTest; testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $$BrainstormOrTestID; Value:Get (RecordID) ]
If [ $$add = 1 and $$citationMatch = $$addCitationMatch ]
Else If [ $$add = "" ]
End If
Refresh Window
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
// If [ TEMP::TLTestSort = "" ]
Set Field [ TEMP::TLTestSort; 1 ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Select Window [ Name: "Learn"; Current file ]
Perform Script [ “sortTestOrBrainstormTaggedLearnRecords” ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$tagtest; Value:testSubsectionTemplate::_LtestSubsection ]
// End If
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
End If
#
#If the user is coming from a test info screen,
#go to the testlearn record they are
#interested in editing and clear the
#$$editTestInfo variable.
If [ $$editTestInfo = 1 ]
Set Variable [ $$editTestInfo ]
Select Window [ Name: "Learn"; Current file ]
End If
#
#Unlike 'exit script', 'halt script' will halt all scripts
#currently active. So if user was on another tag
#record and then clicked on the add tag button
#for another record, this script will launch.
#Problem is, because the user may really
#want to add this tag to the current item in the
#Learn window, after this script runs and finds
#zero records for example (which could happen)
#the add to tag script will run right after it, but
#it will fail to sort the records in the Learn window
#by order number, which this script
#(loadITemRecrodForTestTagMenu) is supposed to
#do everytime. The problem is a record for this
#tag record will exist after the addtotag script has
#run, but this script will not know that having run
#first. So the user will be left wondering, "how is
#that everytime I click on a new test or brainstorm tag
#record that has record tagged with it in the Learn
#window, the Learn window is sorted by order number
#except for this time? How did this fail to happen?"
#Well, it failed for the reason given above and
#the sollution below is to use the 'Halt Script"
#command, which will force the user to click
#the add to tag button a second time to add the
#tag (the first time being when the user clicked
#it to move the system to this record, which
#triggered this loadItem... script.
Halt Script
End If
#
