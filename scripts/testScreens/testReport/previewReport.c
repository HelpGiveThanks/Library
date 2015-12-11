testScreens: testReport: previewReport
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Field [ ]
Select Window [ Name: "Preview"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Preview" ]
Go to Layout [ “PrintReportPreview” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Specified Sort Order: ruleTestReport::name; ascending
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
Sort Records [ Specified Sort Order: ruleTestReport::name; ascending
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
Show Custom Dialog [ Message: "Click the 'exit preview' button to close this window. Click the page numbers (upper left corner) to see
additional pages if there are any."; Buttons: “OK” ]
#
#Change menu to allow user to enter browse mode
#which makes the 'exit preview' button clickable.
#Menu also adds ability to browse records, which
#is essential for allowing user to browse pages of report.
Install Menu Set [ “HGT Preview” ]
Set Variable [ $$preview; Value:1 ]
December 11, ଘ౮27 1:20:24 Library.fp7 - previewReport -1-
