testScreens: testReport: previewReport
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
Select Window [ Name: "Preview"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Preview" ]
Go to Layout [ “PrintReportPreview” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Enter Browse Mode
Enter Preview Mode
Show/Hide Status Area
[ Lock; Show ]
End If
If [ report::ktest ≠ $$item ]
Go to Layout [ “PrintReportPreview” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Enter Browse Mode
Enter Preview Mode
Show/Hide Status Area
[ Lock; Show ]
Exit Script [ ]
End If
Set Variable [ $page; Value:Get (PageNumber) ]
Enter Browse Mode
Enter Preview Mode
Go to Record/Request/Page [ $page ]
[ No dialog ]
Show Custom Dialog [ Message: "Click the 'exit preview' button to close this window. Click the page numbers (upper left corner) to see additional pages if there are any."; Buttons: “OK” ]
Set Variable [ $$preview; Value:1 ]
January 7, 平成26 14:41:07 Imagination Quality Management.fp7 - previewReport -1-
