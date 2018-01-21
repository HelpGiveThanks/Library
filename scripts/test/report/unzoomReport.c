January 15, 2018 15:40:25 Library.fmp12 - unzoomReport -1-
test: report: unzoomReport
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$first ]
Set Variable [ $$last; Value:report::ktestSubsection ]
Set Field [ TEMP::ktestSection; "" ]
#[by David Matson 4.16.11, last modified by same 4.18.11]
#clear the $$finding and $window variables
Set Variable [ $$finding ]
Set Variable [ $$window ]
Set Variable [ $testSubject; Value:report::ktestSubject ]
Set Variable [ $testSubsection; Value:report::ktestSubsection ]
#basic administration tasks
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menu"; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: Get ( ScreenWidth )
/ 2; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; $testSubject ]
Set Field [ testlearnReportTags::ktestSubsection; $testSubsection ]
Set Field [ testlearnReportTags::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::subsectionCustomName; ascending
testlearnReportTags::timestamp; ascending
testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
End If
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: Get
( ScreenWidth ) / 2 ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
// If [ Get (WindowZoomLevel) = 100 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 480; Top: 0; Left: 0 ]
// Set Zoom Level [ 150% ]
// Else If [ Get (WindowZoomLevel) = 150 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 634; Top: 0; Left: 0 ]
// Set Zoom Level [ 200%; Camera: Back; Resolution: Full; Types: Code 39, Code 93, Code 128, EAN-8, EAN-13, EAN/UPC
Composite, GS1 2-Digit Add-On, GS1 5-Digit Add-On, GS1 DataBar Expanded, GS1 DataBar (RSS), ITF-14, ISBN-10 (from
EAN-13), ISBN-13 (from EAN-13), QR Code, UPC-A, UPC-E, Codabar ]
// Else If [ Get (WindowZoomLevel) = 200 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 942; Top: 0; Left: 0 ]
// Set Zoom Level [ 300% ]
// End If
Select Window [ Name: "Report"; Current file ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: 0 ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
