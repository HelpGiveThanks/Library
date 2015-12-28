pictures: pictureInsert
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#REPLACE MEDIA
#
#
#Reference — replace media.
If [ reference::picture ≠ "" and reference::lock = "" or
reference::picture = "" and reference::lock = "" and reference::showMedia ≠ "" and reference::URL ≠ "" ]
If [ $$replaceButton = 1 ]
Show Custom Dialog [ Message: "Replace current picture or movie?"; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ reference::picture ]
Insert Picture [ ]
Go to Field [ ]
If [ reference::picture ≠ "" ]
Set Field [ reference::showMedia; "" ]
End If
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ reference::picture ]
Insert QuickTime [ ]
Go to Field [ ]
If [ reference::picture ≠ "" ]
Set Field [ reference::showMedia; "" ]
End If
End If
Else
Go to Field [ reference::picture ]
End If
#
#
#TestLearn — replace media.
Else If [ testlearn::Picture ≠ "" ]
If [ $$replaceButton = 1 ]
Show Custom Dialog [ Message: "Replace current picture or movie?"; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ testlearn::Picture ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ testlearn::Picture ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Else
Go to Field [ testlearn::Picture ]
End If
#
#
#TestLearnReportTags — replace media.
Else If [ testlearnReportTags::Picture ≠ "" ]
If [ $$replaceButton = 1 ]
Show Custom Dialog [ Message: "Replace current picture or movie?"; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ testlearnReportTags::Picture ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ testlearnReportTags::Picture ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Else
Go to Field [ testlearn::Picture ]
End If
#
#
#INSERT MEDIA INTO AN EMPTY FIELD
#
#
#TestLearnReportTags — insert media into empty field.
Else If [ testlearnReportTags::Picture = "" and $$replaceButton = 1 ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ testlearnReportTags::Picture ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ testlearnReportTags::Picture ]
Insert QuickTime [ ]
Go to Field [ ]
End If
#
#
#Test — insert media into empty field.
Else If [ Get ( LayoutTableName ) = "test" ]
If [ groupTest::testReportPicture = "" ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ groupTest::testReportPicture ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ groupTest::testReportPicture ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Exit Script [ ]
End If
#
#GroupTest — insert media into empty field.
Show Custom Dialog [ Message: "Replace current picture/movie or delete it?"; Buttons: “cancel”, “replace”, “delete” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Go to Field [ groupTest::testReportPicture ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Go to Field [ groupTest::testReportPicture ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Else If [ Get ( LastMessageChoice ) = 3 ]
Set Field [ groupTest::testReportPicture; "" ]
Go to Field [ ]
End If
End If
#
#
December 27, ଘ౮27 18:59:43 Library.fp7 - pictureInsert -1-
