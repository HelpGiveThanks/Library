January 15, 2018 15:06:56 Library.fmp12 - loadSubsection -1-
test: test: loadSubsection
#
#Used on testing subjection selection layout,
#which the library goes to after the user clicks
#a 'test' button on the setup test layout.
#
#Prevents user activating any buttons, until the
#record is loaded.
Set Variable [ $$stopLoadingTestSubSection; Value:1 ]
#
#Prepare to enter in subsection if user clicks
#this subsection's button.
Set Variable [ $$testSubsection; Value:testSubsectionForSubject::_LtestSubsection ]
Set Variable [ $$testSubsectionName; Value:testSubsectionForSubject::name ]
Set Field [ TEMP::testSubsectionName; testSubsectionForSubject::name ]
Set Field [ TEMP::ktestSubsection; testSubsectionForSubject::_LtestSubsection ]
#
Go to Field [ ]
#
