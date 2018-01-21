January 15, 2018 16:07:30 Library.fmp12 - printThingReport -1-
test: report: print: printThingReport
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Close Window [ Name: "Tag Menus"; Current file ]
#find all contact records, sort them, enter preview (print) mode
Go to Layout [ “PrintReport” (report) ]
Set Variable [ $testSubject; Value:report::ktestSubject ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: ruleTestReport::name; ascending
reportSubsection::name; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#allow user to preview report will clicking a button in
#a new window to input page numbers for each item
Enter Preview Mode
Set Window Title [ Current Window; New Title: "Report" ]
Move/Resize Window [ Name: "Report"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
New Window [ Name: "Numbers"; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2; Style: Document; Close: “Yes”;
Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
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
Select Window [ Name: "Numbers"; Current file ]
Loop
Set Variable [ $duplicate; Value:report::ktestSubsection ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ report::ktestSubsection = $duplicate ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
End Loop
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
Pause/Resume Script [ Indefinitely ]
#refind all report records omitted for page numbering
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: ruleTestReport::name; ascending
reportSubsection::name; ascending ]
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
Close Window [ Name: "Report"; Current file ]
Adjust Window
[ Resize to Fit ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Go to Layout [ “reportCover” (report) ]
Enter Browse Mode
Go to Record/Request/Page
[ First ]
Pause/Resume Script [ Indefinitely ]
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
Show Custom Dialog [ Message: "The report cover, table of contents, and report should now be saved as 3 PDFs. In the print
dialogue box select the PDF option (bottom left corner) and save this first PDF as cover."; Default Button: “OK”, Commit:
“No” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore: Bluetooth ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Print Setup [ Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore; No dialog ]
Save Records as PDF [ File Name: “$path/$pdf”; Current record ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magnification: 100% ]
[ Restore; No dialog ]
End If
#
#pdf table of contents
Go to Layout [ “TOCpdf” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: report::TOC; ascending
ruleTestReport::name; ascending
reportSubsection::name; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $duplicate; Value:report::ktestSubsection ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ report::ktestSubsection = $duplicate ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
End Loop
Enter Preview Mode
If [ Left ( Get (ApplicationVersion) ; 3) = "run" and Get ( SystemPlatform ) ≠ 3 ]
Show Custom Dialog [ Message: "Save this second PDF as TOC."; Default Button: “OK”, Commit: “No” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore: EPSON WorkForce 630 ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Save Records as PDF [ File Name: “$path/$pdf”; Records being browsed ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magnification: 100% ]
[ Restore; Append; No dialog ]
End If
#
#pdf report
Go to Layout [ “PrintReport” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: ruleTestReport::name; ascending
reportSubsection::name; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Enter Preview Mode
If [ Left ( Get (ApplicationVersion) ; 3) = "run" and Get ( SystemPlatform ) ≠ 3 ]
Show Custom Dialog [ Message: "Save this third PDF as Report."; Default Button: “OK”, Commit: “No” ]
Print [ Records being browsed; All Pages; Orientation: Portrait; Paper size: 8.5" x 11" ]
[ Restore: EPSON WorkForce 630 ]
Show Custom Dialog [ Message: "Open up all three PDFs. Drag the cover and TOC page thumbnails into the Report.pdf along
with any other PDF thumbnails you wish from Preview's sidebar. Save this PDF. Trash the other two."; Default Button: “OK”,
Commit: “No” ]
Else If [ Left ( Get (ApplicationVersion) ; 3) ≠ "run" or Get ( SystemPlatform ) = 3 ]
Save Records as PDF [ File Name: “$path/$pdf”; Automatically open; Records being browsed ]
[ Document - Compatibility: Acrobat 5 and later ]
[ Pages - Number Pages From: 1; Include: All pages ]
[ Security - Printing: High Resolution; Editing: Any except extracting pages; Enable copying; Enable Screen Reader ]
[ Initial View - Show: Pages Panel and Page; Page Layout: Default; Magnification: 100% ]
[ Restore; Append; No dialog ]
End If
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Name: "Setup"; Current file; Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
New Window [ Name: "Tag Menus"; Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2; Style: Document; Close: “Yes”;
Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
// Perform Script [ “templateTestSectionMenu (update and name change from defaultTestLocationMenu)” ]
Perform Script [ “editReport (update)” ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
