learn: showFileInTagandLearnWindows
#
#Show reference file.
If [ FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; " " ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( reference::fileName ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( reference::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; " " ) &
Case ( Left ( reference::fileName ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; " " ) ;
 "/" & Substitute ( reference::fileName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
End If
#
#Show cite file from testlearn window.
If [ FilterValues ( citeCite::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeCite::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeCite::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( citeCite::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeCite::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeCite::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( citeCite::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & TLciteFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeCite::fileName ; 1 ) = "/" ; Substitute ( citeCite::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( citeCite::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & TLciteFolderPath::tag ; " " ; " " ) &
Case ( Left ( citeCite::fileName ; 1 ) = "/" ; Substitute ( citeCite::fileName ; " " ; " " ) ;
 "/" & Substitute ( citeCite::fileName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
End If
#
#Show 1st ref file from testlearn window.
If [ FilterValues ( refReference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refReference::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refReference::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( refReference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refReference::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refReference::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( refReference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & TLrefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refReference::fileName ; 1 ) = "/" ; Substitute ( refReference::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( refReference::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & TLrefFolderPath::tag ; " " ; " " ) &
Case ( Left ( refReference::fileName ; 1 ) = "/" ; Substitute ( refReference::fileName ; " " ; " " ) ;
 "/" & Substitute ( refReference::fileName ; " " ; " " ) ) ]
[ No dialog ]
May 10, 平成27 11:26:39 Library.fp7 - showFileInTagandLearnWindows -1-
learn: showFileInTagandLearnWindows
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
End If
#
#Show cite file from test info window.
If [ FilterValues ( citeTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeTest::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeTest::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( citeTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeTest::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeTest::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( citeTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & citeTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeTest::fileName ; 1 ) = "/" ; Substitute ( citeTest::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( citeTest::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & citeTestFolderPath::tag ; " " ; " " ) &
Case ( Left ( citeTest::fileName ; 1 ) = "/" ; Substitute ( citeTest::fileName ; " " ; " " ) ;
 "/" & Substitute ( citeTest::fileName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
End If
#
#Show 1st reference file from test info window.
If [ FilterValues ( refTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refTest::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refTest::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refTest::fileName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refTest::fileName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the first reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refTest::fileName ; 1 ) = "/" ; Substitute ( refTest::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( refTest::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; " " ) &
Case ( Left ( refTest::fileName ; 1 ) = "/" ; Substitute ( refTest::fileName ; " " ; " " ) ;
 "/" & Substitute ( refTest::fileName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The file has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::fileName & "."; Buttons: “OK” ]
End If
End If
#
// #Show TestLearn file.
// If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Open URL [ Substitute ( tagRefFolderPath::tag ; " " ; "%20" ) & Substitute ( testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Else If [ testlearn::URL ≠ "" ]
// Open URL [ testlearn::URL ]
[ No dialog ]
// End If
May 10, 平成27 11:26:39 Library.fp7 - showFileInTagandLearnWindows -2-
