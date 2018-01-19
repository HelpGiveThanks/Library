January 12, 2018 13:58:32 Library.fmp12 - gotoTestSubject_SectionField -1-
test: setup: gotoTestSubject_SectionField
#
#
#Test subject is locked.
If [ testSubjectName::orderOrLock ≠ "" ]
Go to Field [ testSectionCreatedFromATemplate::nameOnTestResult ]
#Test subject is not locked.
Else
Go to Field [ testSectionCreatedFromATemplate::name ]
End If
#
#
