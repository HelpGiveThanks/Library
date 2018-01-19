January 10, 2018 15:12:36 Library.fmp12 - subsectionLoop -1-
dataCleanUpScripts: subsectionLoop
#
#Use this script to change some information in all
#records currently found. Useful for when you make
#an error covering many records to correct the error.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Show All Records
Go to Record/Request/Page
[ First ]
Loop
#
Set Field [ testSubsectionTemplate::order[2]; testSubsectionTemplate::order[1] ]
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup:
“"testItemGroup"” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Loop
#
Set Field [ testSubsectionGroup::orderOrLibraryType[2]; testSubsectionGroup::orderOrLibraryType[1] ]
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::match: “"testSubsection"” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Loop
#
Set Field [ testSubsectionGroup::orderOrLibraryType[2]; testSubsectionGroup::orderOrLibraryType[1] ]
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “tableTag” (tagTable) ]
Perform Find [ Specified Find Requests: Find Records
Find Records; Criteria: tagTable::match: “"testItem"” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Loop
#
Set Field [ tagTable::orderOrLock[2]; tagTable::orderOrLock[1] ]
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
