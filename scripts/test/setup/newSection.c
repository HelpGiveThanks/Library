January 12, 2018 14:26:37 Library.fmp12 - newSection -1-
test: setup: newSection
#
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Create new section that can be added to
#any subject's test.
New Record/Request
Set Field [ testSection::match; "testSection" ]
Set Field [ testSection::tag; "section_template" ]
Set Field [ testSection::tagSpelling; "section_template" ]
Set Field [ testSection::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Go to Field [ testSection::tag ]
#
