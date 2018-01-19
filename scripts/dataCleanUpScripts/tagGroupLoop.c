January 10, 2018 15:26:47 Library.fmp12 - tagGroupLoop -1-
dataCleanUpScripts: tagGroupLoop
#
#Use this script to change some information in all
#records currently found. Useful for when you make
#an error covering many records to correct the error.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Show All Records
Go to Record/Request/Page
[ First ]
Loop
#
If [ testSubsectionGroup::match = "health" ]
Set Field [ testSubsectionGroup::match; "copyright" ]
End If
#
If [ testSubsectionGroup::match = "section" ]
Set Field [ testSubsectionGroup::match; "library" ]
End If
#
If [ testSubsectionGroup::match = "organ" ]
Set Field [ testSubsectionGroup::match; "publication" ]
End If
#
If [ testSubsectionGroup::match = "copyist" ]
Set Field [ testSubsectionGroup::match; "publisher" ]
End If
#
If [ testSubsectionGroup::match = "sample" ]
Set Field [ testSubsectionGroup::match; "brainstorm" ]
End If
#
If [ testSubsectionGroup::match = "focus" ]
Set Field [ testSubsectionGroup::match; "testSection" ]
End If
#
If [ testSubsectionGroup::match = "testGroup" ]
Set Field [ testSubsectionGroup::match; "testSubsection" ]
End If
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]
