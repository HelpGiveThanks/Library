reference(citation): showFolder
#
#Show folder ﬁle is in Reference.
If [ FilterValues ( reference::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: reference::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: reference::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: reference::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on ﬁle is " & tagRefFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder for cite ﬁle in Learn.
If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: citeCite::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: citeCite::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: citeCite::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & TLciteFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeCite::ﬁleName ; 1 ) = "/" ; Substitute ( citeCite::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on ﬁle is " & TLciteFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder for 1st ref ﬁle in Learn.
If [ FilterValues ( refTest::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( refTest::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( refTest::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & refTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refTest::ﬁleName ; 1 ) = "/" ; Substitute ( refTest::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on ﬁle is " & refTestFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder cite ﬁle is in Test.
If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: citeTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: citeTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: citeTest::ﬁleName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & citeTestFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on ﬁle is " & citeTestFolderPath::tag; Buttons: “OK” ]
End If
End If
#
// #
// #Show folder ﬁle is in.
// If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Show Custom Dialog [ Message: testlearn::ﬁlename; Buttons: “OK” ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Show Custom Dialog [ Message: testlearn::ﬁlename; Buttons: “OK” ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Show Custom Dialog [ Message: testlearn::ﬁlename; Buttons: “OK” ]
// Open URL [ Substitute ( tagTLFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
// End If
January 7, 平成26 17:58:34 Imagination Quality Management.fp7 - showFolder -1-
