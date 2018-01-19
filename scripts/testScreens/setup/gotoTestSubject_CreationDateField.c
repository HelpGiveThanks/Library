January 12, 2018 14:02:18 Library.fmp12 - gotoTestSubject_CreationDateField -1-
test: setup: gotoTestSubject_CreationDateField
#
#
#Test subject is not locked.
If [ testSubjectName::orderOrLock = "" ]
Go to Field [ testSectionCreatedFromATemplate::creationDate ]
End If
#
#
