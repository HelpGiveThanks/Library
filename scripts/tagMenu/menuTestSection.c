January 15, 2018 16:27:37 Library.fmp12 - menuTestSection -1-
tagMenu: menuTestSection
#
#Go to the test section layout.
Go to Layout [ “setupTestSection” (testSection) ]
#
#Clear the citation match variable.
Set Variable [ $$citationMatch ]
#
#Find all test sections for this library.
Set Error Capture [ On ]
Allow User Abort [ Off ]
View As
[ View as List ]
Enter Find Mode [ ]
Set Field [ testSection::match; "testSection" ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSection::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Perform Script [ “checkTestSectionSubsectionAndItemRecordSpellings (update)” ]
#
