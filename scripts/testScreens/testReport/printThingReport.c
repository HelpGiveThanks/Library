testScreens: testReport: Print: PrintThingReport
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Close Window [ Name: "Tag Menus"; Current ﬁle ]
#ﬁnd all contact records, sort them, enter preview (print) mode
Go to Layout [ “PrintReport” (report) ]
Set Variable [ $contact; Value:report::ktestSubject ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#allow user to preview report will clicking a button in
#a new window to input page numbers for each item
Enter Preview Mode
Set Window Title [ Current Window; New Title: "Report" ]
Move/Resize Window [ Name: "Report"; Current ﬁle; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
New Window [ Name: "Numbers"; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
Enter Browse Mode
// Arrange All Windows
[ Tile Vertically ]
Go to Layout [ “pageNumbering” (report) ]
Go to Record/Request/Page
[ First ]
Set Field [ report::pagenumberTheme; 1 ]
Set Field [ report::CurrentRecord; Get ( RecordID ) ]
Set Variable [ $$themepage; Value:2 ]
Set Field [ TEMP::pageNumber; 1 ]
Select Window [ Name: "Numbers"; Current ﬁle ]
Loop
Set Variable [ $duplicate; Value:report::ktest ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ report::ktest = $duplicate ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
End Loop
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
Pause/Resume Script [ Indeﬁnitely ]
#reﬁnd all report records omitted for page numbering
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#now save the TOC to every report record in case the one showing gets deleted.
Set Variable [ $TOC; Value:report::TOC ]
Set Variable [ $TOCnumbers; Value:report::TOCnumbers ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ report::TOC; $TOC ]
Set Field [ report::TOCnumbers; $TOCnumbers ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $path; Value:Get ( TemporaryPath ) ]
Close Window [ Name: "Report"; Current ﬁle ]
Adjust Window
[ Resize to Fit ]
Set Zoom Level
[ 100% ]
Go to Layout [ “reportCover” (report) ]
Enter Browse Mode
Go to Record/Request/Page
[ First ]
Pause/Resume Script [ Indeﬁnitely ]
#
#pdf report cover
Set Variable [ $cover; Value:report::ReportCover ]
Set Variable [ $pdf; Value:report::ReportPDFtitle ]
Go to Record/Request/Page
[ First ]
Set Variable [ $printcover; Value:report::_Lreport ]
Loop
Set Field [ report::ReportCover; $cover ]
Set Field [ report::ReportPDFtitle; $pdf ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Enter Find Mode [ ]
Set Field [ report::_Lreport; $printcover ]
Perform Find [ ]
If [ Left ( Get (ApplicationVersion) ; 3) = "run" and Get ( SystemPlatform ) ≠ 3 ]
Show Custom Dialog [ Message: "The report cover, table of contents, and report should now be saved as 3 PDFs. In the print dialogue box select the PDF option (bottom left corner) and save this ﬁrst PDF as cover."; Buttons: “OK” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore; No dialog ]
Save Records as PDF [ File Name: “$path/$pdf”; Current record ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magniﬁcation: 100% ]
[ Restore; No dialog ]
End If
#
#pdf table of contents
Go to Layout [ “TOCpdf” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: report::TOC; ascending
ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
January 7, 平成26 14:45:57 Imagination Quality Management.fp7 - PrintThingReport -1-testScreens: testReport: Print: PrintThingReport
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $duplicate; Value:report::ktest ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ report::ktest = $duplicate ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
End Loop
Enter Preview Mode
If [ Left ( Get (ApplicationVersion) ; 3) = "run" and Get ( SystemPlatform ) ≠ 3 ]
Show Custom Dialog [ Message: "Save this second PDF as TOC."; Buttons: “OK” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Save Records as PDF [ File Name: “$path/$pdf”; Records being browsed ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magniﬁcation: 100% ]
[ Restore; Append; No dialog ]
End If
#
#pdf report
Go to Layout [ “PrintReport” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: ruleTestReport::name; ascending
reportItem::testName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Enter Preview Mode
If [ Left ( Get (ApplicationVersion) ; 3) = "run" and Get ( SystemPlatform ) ≠ 3 ]
Show Custom Dialog [ Message: "Save this third PDF as Report."; Buttons: “OK” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore ]
Show Custom Dialog [ Message: "Open up all three PDFs. Drag the cover and TOC page thumbnails into the Report.pdf along with any other PDF thumbnails you wish from Preview's sidebar. Save this PDF. Trash the other two."; Buttons: “OK” ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Save Records as PDF [ File Name: “$path/$pdf”; Automatically open; Records being browsed ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magniﬁcation: 100% ]
[ Restore; Append; No dialog ]
End If
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Name: "Setup"; Current ﬁle; Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Go to Layout [ “defaultSetup” (tempSetup) ]
New Window [ Name: "Tag Menus"; Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2 ]
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
// Perform Script [ “defaultTestLocationMenu” ]
Perform Script [ “EditReport” ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
January 7, 平成26 14:45:57 Imagination Quality Management.fp7 - PrintThingReport -2-
