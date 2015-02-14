reference(citation): showFolder
#
#Show folder file is in Reference.
If [ FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: reference::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: reference::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: reference::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on file is " & tagRefFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder for cite file in Learn.
If [ FilterValues ( citeCite::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: citeCite::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeCite::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: citeCite::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeCite::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: citeCite::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & TLciteFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeCite::fileName ; 1 ) = "/" ; Substitute ( citeCite::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on file is " & TLciteFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder for 1st ref file in Learn.
If [ FilterValues ( refTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: refTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refTest::fileName ; 1 ) = "/" ; Substitute ( refTest::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on file is " & refTestFolderPath::tag; Buttons: “OK” ]
End If
End If
#
#Show folder cite file is in Test.
If [ FilterValues ( citeTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Show Custom Dialog [ Message: citeTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Show Custom Dialog [ Message: citeTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citeTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Show Custom Dialog [ Message: citeTest::fileName; Buttons: “OK” ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & citeTestFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder has been moved, deleted, or the external drive this folder is on is not plugged in. The folder path on file is " & citeTestFolderPath::tag; Buttons: “OK” ]
End If
End If
#
// #
// #Show folder file is in.
// If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Show Custom Dialog [ Message: testlearn::filename; Buttons: “OK” ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Show Custom Dialog [ Message: testlearn::filename; Buttons: “OK” ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Show Custom Dialog [ Message: testlearn::filename; Buttons: “OK” ]
// Open URL [ Substitute ( tagTLFolderPath::tag ; " " ; "%20" ) ]
[ No dialog ]
// End If
January 7, 平成26 17:58:34 Imagination Quality Management.fp7 - showFolder -1-
