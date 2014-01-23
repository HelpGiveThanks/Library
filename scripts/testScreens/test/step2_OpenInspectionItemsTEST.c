testScreens: test: step2_OpenInspectionItemsTEST
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$TSRecordNumber; Value:Get (RecordNumber) ]
Go to Field [ ]
#
If [ TEMP::ksection = "" ]
Go to Field [ TEMP::ksection ]
[ Select/perform ]
Halt Script
Else If [ TEMP::reportNumber = "" ]
Go to Field [ TEMP::reportNumber ]
[ Select/perform ]
Halt Script
Else If [ tagTestSubjectLocation::focusName = "" ]
Halt Script
End If
Set Field [ TEMP::kdefaultNodeTestSubject; tagTestSubjectLocation::knode ]
Set Field [ tagTestSubjectLocation::TimeStart; Get ( CurrentTime ) ]
Set Variable [ $status; Value:tagTestSubjectLocation::inUse ]
Set Variable [ $$timeRecord; Value:Get ( RecordNumber ) ]
Set Variable [ $$library; Value:TEMP::ksection ]
#
#!!!need to go through database and remove all variables like $$reportnumber that are used in mulitple scripts and make it a temp ﬁeld.
Set Variable [ $$reportnumber; Value:tagTestSubjectLocation::reportNumber ]
Set Field [ TEMP::reportNumber; tagTestSubjectLocation::reportNumber ]
Set Variable [ $$contact; Value:TEMP::kdefaultNodeTestSubject ]
#
#note general or canned location user identiﬁed
Set Variable [ $$locationName; Value:tagTestSubjectLocation::focusName ]
Set Field [ TEMP::LocationName; TextStyleAdd ( $$locationName ; Titlecase ) ]
#
#note new location ID number and name user created for this speciﬁc location in the contact's building
Set Variable [ $$location; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Set Variable [ $$itemLocation; Value:tagTestSubjectLocation::kfocus ]
#
#Goto no tag layout in Tag Menus as this next
#main screen is for selection only. It does not
#show any records that the user might want to
#tag. I thought about closing the Tag Menus
#window, but in testing it was odd, and so better
#just to keep the window open and show no tags
#but do change its layout to the look and feel
#of the layouts the user will see in test mode
#in the Tag Menus window.
Go to Layout [ “testMenuNoTag” (TEMP) ]
Select Window [ Name: "Setup"; Current ﬁle ]
#
Set Field [ TEMP::testerAndsubject; //tagDefaultNodePrimary::tag & " testing " & ¶ & $testsubjectName & "'s"& ¶ & tempSetup::sectionName
//$testsubjectName & ¶ & $$locationName & ¶ & tempSetup::sectionName
//tempSetup::sectionName & " | " & $testsubjectName
tempSetup::sectionName & " | " & tagDefaultTestSubject::tag ]
Set Window Title [ Current Window; New Title: "Test" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Enter Find Mode [ ]
#
#now ﬁnd and show all canned inspection items associated with this generic canned location
Set Field [ InspectItems::kcfocusALL; $$itemLocation ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Show Custom Dialog [ Title: "!"; Message: "No items have been assigned to this area for assessment."; Buttons: “OK” ]
Exit Script [ ]
End If
// If [ PatternCount ( Get ( ApplicationVersion ) ; "GO" ) = "GO" ]
Sort Records [ Speciﬁed Sort Order: ruleTestInpsection::name; ascending
InspectItems::order; based on value list: “order” ]
[ Restore; No dialog ]
Set Field [ InspectItems::glocationNameGlobal; $$locationName ]
Set Field [ InspectItems::kgaudienceLocation; $$location ]
Set Field [ InspectItems::gcontactNameGlobal; $$testsubjectName ]
Set Field [ InspectItems::kgreportNumber; $$reportNumber ]
Set Field [ InspectItems::kgtester; TEMP::kdefaultNodeTestSubject ]
If [ $status = "" ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
Scroll Window
[ Home ]
Exit Script [ ]
Else If [ $status = "t" ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Scroll Window
[ Home ]
Exit Script [ ]
End If
Set Field [ InspectItems::gprogressGlobal; "status: done" ]
Scroll Window
[ Home ]
January 7, 平成26 12:27:14 Imagination Quality Management.fp7 - step2_OpenInspectionItemsTEST -1-
