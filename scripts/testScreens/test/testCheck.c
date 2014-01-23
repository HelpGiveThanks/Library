testScreens: test: TestCheck
If [ Get ( ActiveFieldContents ) = "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "You need to create a test by clicking the 'new/edit' test button above, before you can create a focus for your test. Sorry if this is confusing. As youhe test focus screen (this screen) before you can see the test create screen. "; Buttons: “OK” ]
End If
January 7, 平成26 12:22:38 Imagination Quality Management.fp7 - TestCheck -1-
