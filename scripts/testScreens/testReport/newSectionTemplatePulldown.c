January 12, 2018 14:48:25 Library.fmp12 - newTestSectionTemplatePulldownCheck -1-
test: setup: newTestSectionTemplatePulldownCheck
#
#
#If there are no test sections created,
#tell the user this, and how to create some.
If [ ValueListItems ( Get ( FileName ) ; "defaultSectionTemplates" ) = "" ]
Show Custom Dialog [ Message: "There are no test-section templates available for creating new test sections. To create some 1)
click 'back', then 2) click 'section-templatesetup' and finally 3) click 'new' to create your first test-section template. 4)
Customize it to meet your needs."; Default Button: “OK”, Commit: “Yes” ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
