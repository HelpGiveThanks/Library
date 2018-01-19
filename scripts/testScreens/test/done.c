January 15, 2018 15:11:36 Library.fmp12 - done -1-
test: test: done
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Freeze Window
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testSubsectionForSubject::kcsections; $$testSectionTemplate ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Exit Script [ ]
End If
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
If [ testSectionCreatedFromATemplate::inUse = "t" ]
Set Field [ testSectionCreatedFromATemplate::inUse; "d" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: done" ]
Exit Script [ ]
End If
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
