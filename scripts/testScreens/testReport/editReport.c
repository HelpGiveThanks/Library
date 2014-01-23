testScreens: testReport: EditReport
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
Set Field [ TEMP::kabout; TEMP::kdefaultNodeTestSubject ]
Set Variable [ $$contact; Value:TEMP::kdefaultNodeTestSubject ]
#
#clear global ﬁelds for creating new discovery
#records, but put in current timestamp to help
#user understand how info sould be put into
#the timestample ﬁeld and for easy editing,
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
#go to correct layout for ﬁnal part of script to
#to ﬁnd discoveries for the report item.
Set Field [ TEMP::showFavorites; "" ]
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
#
Select Window [ Name: "Setup"; Current ﬁle ]
Set Field [ TEMP::testerAndsubject; //tagDefaultNodePrimary::tag & " testing " & ¶ & $testsubjectName & "'s"& ¶ & tempSetup::sectionName
//$testsubjectName & ¶ & $$locationName & ¶ & tempSetup::sectionName
//tempSetup::sectionName & " | " & $testsubjectName
tempSetup::sectionName & " | " & tagDefaultTestSubject::tag & " | " & "report " & $$reportNumber ]
Set Window Title [ Current Window; New Title: "Report" ]
Scroll Window
[ Home ]
#
#ﬁnd all report pages ﬁrst, then sort them alphabetically
#and go to the ﬁrst records. Use this one to ﬁnd
#only report records for this item.
Enter Find Mode [ ]
Go to Layout [ “PrintReportEdit” (report) ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Perform Find [ ]
If [ Get (LastError) = 401 ]
Perform Script [ “returnToStep2” ]
Show Custom Dialog [ Message: "No test discoveries to report on."; Buttons: “OK” ]
Set Variable [ $$stopLoadReportRecord ]
Exit Script [ ]
End If
Set Variable [ $$stopLoadReportRecord ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Use this ﬁrst record to ﬁnd
#only report records for this item.
#****haven't decided to use globals or $$variables. Since $$item is used in many other scripts I'm capturing it here.
Set Field [ TEMP::testName; reportItem::testName ]
Set Field [ TEMP::ktest; report::ktest ]
Set Field [ TEMP::ktestItemList; report::ktest ]
Set Variable [ $$item; Value:report::ktest ]
Set Variable [ $$ﬁrst; Value:report::ktest ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; TEMP::ktest ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: report::ktest; ascending ]
[ Restore; No dialog ]
#
View As
[ View as List ]
Scroll Window
[ Home ]
#
#Now ﬁnd discoveries for this report item.
Perform Script [ “CHUNK_gotoItemViaPulldown” ]
#
January 7, 平成26 14:25:10 Imagination Quality Management.fp7 - EditReport -1-
