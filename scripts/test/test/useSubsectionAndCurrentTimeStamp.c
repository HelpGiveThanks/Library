January 15, 2018 15:22:13 Library.fmp12 - useSubsectionAndCurrentTimeStamp -1-
test: test: useSubsectionAndCurrentTimeStamp
#
#Set up new test result information with this
#result's information.
Set Field [ TEMP::testSubsectionNameForSubject; tagReportTestSubjectSectionNAME::name ]
Set Field [ TEMP::ktestSection; testlearnReportTags::ktestSection ]
Set Variable [ $$subsectionCustomName; Value:testlearnReportTags::subsectionCustomName ]
Set Field [ testlearnReportTags::kgtestSection; testlearnReportTags::ktestSection ]
Set Field [ TEMP::TimeStamp; testlearnReportTags::timestamp ]
