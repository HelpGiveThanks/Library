testScreens: testReport: editReport
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Field [ TEMP::kuserLocation; "" ]
Set Variable [ $$TSRecordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$stopLoadReportRecord; Value:1 ]
#
#used for item pulldown selection on report layout
Set Field [ TEMP::kdefaultNodeTestSubject; tagTestSubjectLocation::knode ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; tagTestSubject::tag ]
Set Field [ TEMP::kabout; TEMP::kdefaultNodeTestSubject ]
Set Variable [ $$contact; Value:TEMP::kdefaultNodeTestSubject ]
#
#clear global fields for creating new discovery
#records, but put in current timestamp to help
#user understand how info sould be put into
#the timestample field and for easy editing,
#changing date, time, etc.
Set Field [ testlearnReportTags::gkaudienceLocation; "" ]
Set Field [ TEMP::LocationName; "" ]
Set Field [ TEMP::TimeStamp; Get ( CurrentTimeStamp ) ]
#
If [ TEMP::ksection = "" ]
Go to Field [ TEMP::ksection ]
[ Select/perform ]
Show Custom Dialog [ Message: "Select a section before editing a report."; Buttons: “OK” ]
Halt Script
Else If [ TEMP::reportNumber = "" ]
Set Field [ ]
Go to Field [ TEMP::reportNumber ]
[ Select/perform ]
Halt Script
End If
Set Variable [ $$library; Value:TEMP::ksection ]
Set Variable [ $$reportNumber; Value:tagTestSubjectLocation::reportNumber ]
Set Field [ TEMP::reportNumber; tagTestSubjectLocation::reportNumber ]
#
#go to correct layout for final part of script to
#to find discoveries for the report item.
Set Field [ TEMP::showFavorites; "" ]
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
#
#Change window name to Report.
Select Window [ Name: "Setup"; Current file ]
Set Field [ TEMP::testerAndsubject; //tagDefaultNodePrimary::tag & " testing " & ¶ & $testsubjectName & "'s"& ¶ & tempSetup::
sectionName
//$testsubjectName & ¶ & $$locationName & ¶ & tempSetup::sectionName
//tempSetup::sectionName & " | " & $testsubjectName
tempSetup::sectionName & " | " & tagDefaultTestSubject::tag & " | " & "report " & $$reportNumber ]
Set Window Title [ Current Window; New Title: "Report" ]
Scroll Window
[ Home ]
#
#Resize Report Window if needed to show full
#layout. If it is resized then also resize Tag
#Menus to fit in the remaining, smaller space.
Go to Layout [ “PrintReportEdit” (report) ]
Adjust Window
[ Resize to Fit ]
Set Variable [ $reportWindowSize; Value:Get ( WindowWidth ) ]
If [ $reportWindowSize > Get ( ScreenWidth ) / 2 ]
Select Window [ Name: "Tag Menus"; Current file ]
Move/Resize Window [ Current Window; Width: Get (ScreenWidth) - $reportWindowSize; Left: $reportWindowSize ]
Select Window [ Name: "Report"; Current file ]
Else
Move/Resize Window [ Current Window; Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
End If
#
#find all report pages first, then sort them alphabetically
#and go to the first records. Use this one to find
#only report records for this item.
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Perform Find [ ]
If [ Get (LastError) = 401 ]
Perform Script [ “returnToStep2 (update)” ]
Show Custom Dialog [ Message: "No test discoveries to report on."; Buttons: “OK” ]
Set Variable [ $$stopLoadReportRecord ]
Exit Script [ ]
End If
Set Variable [ $$stopLoadReportRecord ]
Sort Records [ Specified Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Use this first record to find
#only report records for this item.
#****haven't decided to use globals or $$variables. Since $$item is used in many other scripts I'm capturing it here.
Set Field [ TEMP::testName; reportItem::testName ]
Set Field [ TEMP::ktest; report::ktest ]
Set Field [ TEMP::ktestItemList; report::ktest ]
Set Variable [ $$item; Value:report::ktest ]
Set Variable [ $$first; Value:report::ktest ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; TEMP::ktest ]
Perform Find [ ]
Sort Records [ Specified Sort Order: report::ktest; ascending ]
[ Restore; No dialog ]
#
View As
[ View as List ]
Scroll Window
[ Home ]
#
#Now find discoveries for this report item.
Perform Script [ “CHUNK_gotoItemViaPulldown” ]
#
December 11, ଘ౮27 1:28:46 Library.fp7 - editReport -1-
