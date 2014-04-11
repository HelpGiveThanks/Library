learn: showFileInTagandLearnWindows
#
#Show reference ﬁle.
If [ FilterValues ( reference::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( reference::ﬁleName ; 1 ) = "/" ; Substitute ( reference::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( reference::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagRefFolderPath::tag ; " " ; " " ) &
Case ( Left ( reference::ﬁleName ; 1 ) = "/" ; Substitute ( reference::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( reference::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
End If
#
#Show cite ﬁle from testlearn window.
If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeCite::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeCite::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeCite::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeCite::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( citeCite::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & TLciteFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeCite::ﬁleName ; 1 ) = "/" ; Substitute ( citeCite::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( citeCite::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & TLciteFolderPath::tag ; " " ; " " ) &
Case ( Left ( citeCite::ﬁleName ; 1 ) = "/" ; Substitute ( citeCite::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( citeCite::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
End If
#
#Show 1st ref ﬁle from testlearn window.
If [ FilterValues ( refReference::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refReference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refReference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( refReference::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refReference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refReference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( refReference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & TLrefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refReference::ﬁleName ; 1 ) = "/" ; Substitute ( refReference::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( refReference::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & TLrefFolderPath::tag ; " " ; " " ) &
Case ( Left ( refReference::ﬁleName ; 1 ) = "/" ; Substitute ( refReference::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( refReference::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
April 11, 平成26 9:56:11 Imagination Quality Management.fp7 - showFileInTagandLearnWindows -1-learn: showFileInTagandLearnWindows
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
End If
#
#Show cite ﬁle from test info window.
If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeTest::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citeTest::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeTest::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citeTest::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( citeTest::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & citeTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( citeTest::ﬁleName ; 1 ) = "/" ; Substitute ( citeTest::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( citeTest::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & citeTestFolderPath::tag ; " " ; " " ) &
Case ( Left ( citeTest::ﬁleName ; 1 ) = "/" ; Substitute ( citeTest::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( citeTest::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
End If
#
#Show 1st reference ﬁle from test info window.
If [ FilterValues ( refTest::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refTest::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & refTest::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Else If [ FilterValues ( refTest::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refTest::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & refTest::ﬁleName ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name has been changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
Exit Script [ ]
Else If [ FilterValues ( refTest::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & refTestFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( refTest::ﬁleName ; 1 ) = "/" ; Substitute ( refTest::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( refTest::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & refTestFolderPath::tag ; " " ; " " ) &
Case ( Left ( refTest::ﬁleName ; 1 ) = "/" ; Substitute ( refTest::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( refTest::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The ﬁle has been deleted, moved from, or never downloaded/moved into " & tagRefFolderPath::tag & "," & " or the external drive it is on is not plugged in, or it's name was changed from " & reference::ﬁleName & "."; Buttons: “OK” ]
End If
End If
#
// #Show TestLearn ﬁle.
// If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Open URL [ Substitute ( tagRefFolderPath::tag ; " " ; "%20" ) & Substitute ( testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
// Else If [ testlearn::URL ≠ "" ]
// Open URL [ testlearn::URL ]
[ No dialog ]
// End If
April 11, 平成26 9:56:11 Imagination Quality Management.fp7 - showFileInTagandLearnWindows -2-