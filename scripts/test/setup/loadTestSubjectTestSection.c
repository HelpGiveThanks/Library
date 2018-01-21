January 12, 2018 14:24:22 Library.fmp12 - loadTestSubjectTestSection -1-
test: setup: loadTestSubjectTestSection
#
#Stop script if running a delete check.
If [ $$stopLoadTestRecord = 1 ]
Exit Script [ ]
End If
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Turn off highlights when leaving editsection
#layout (called defaultTestNewSection).
Set Variable [ $$highlightTestSection ]
Refresh Window
#
#If no section-templates exist then clear the
#section-template key and name fields.
If [ ValueListItems ( Get ( FileName ) ; "defaultSectionTemplates" ) = "" ]
Set Field [ TEMP::DEFAULTSectionName; "" ]
Set Field [ TEMP::kdefaultSectionTemplate; "" ]
End If
#
#If no records exist then stop the script.
If [ Get (FoundCount) = 0 and $$stopFocusLoad = "" or
Get (FoundCount) ≠ 0 and $$stopFocusLoad = 1 or
$$stopSetReportNumber = 1 ]
Exit Script [ ]
End If
#
#Set default test number so any new sections
#will be add to the selected test.
Set Field [ TEMP::reportNumber; testSectionCreatedFromATemplate::reportNumber ]
Go to Field [ ]
#
#Set test subject variable for conditionally
#formatting the selected test.
Set Variable [ $$testSubject; Value:testSectionCreatedFromATemplate::ktestSubjectNode ]
Refresh Window
#
// #Pause prevents accidental click of
// #section pulldown button after 'edit/newtest'
// #button is clicked.
// Set Variable [ $$pause; Value:1 ]
// Pause/Resume Script [ Duration (seconds): .5 ]
// Set Variable [ $$pause ]
#
