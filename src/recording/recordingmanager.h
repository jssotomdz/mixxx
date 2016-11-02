#ifndef RECORDINGMANAGER_H
#define RECORDINGMANAGER_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "preferences/usersettings.h"
#include "control/controlobject.h"
#include "recording/defs_recording.h"

//
// The RecordingManager is a central class and manages
// the recording feature of Mixxx.
//
// There is exactly one instance of this class
//
// All methods in this class are thread-safe
//
// Note: The RecordingManager lives in the GUI thread
//

class EngineMaster;
class ControlPushButton;
class ControlProxy;

class RecordingManager : public QObject
{
    Q_OBJECT
  public:
    RecordingManager(UserSettingsPointer pConfig, EngineMaster* pEngine);
    virtual ~RecordingManager();


    // This will try to start recording. If successful, slotIsRecording will be
    // called and a signal isRecording will be emitted.
    // The method computes the filename based on date/time information.
    void startRecording();
    void stopRecording();
    bool isRecordingActive();
    void setRecordingDir();
    QString& getRecordingDir();
    // Returns the currently recording file
    QString& getRecordingFile();
    QString& getRecordingLocation();

  signals:
    // Emits the cumulative number of bytes currently recorded.
    void bytesRecorded(long);
    void isRecording(bool);
    void durationRecorded(QString);

  public slots:
    void slotIsRecording(bool recording, bool error);
    void slotBytesRecorded(int);
    void slotDurationRecorded(quint64);

  private slots:
    void slotSetRecording(bool recording);
    void slotToggleRecording(double v);

  private:
    QString formatDateTimeForFilename(QDateTime dateTime) const;
    // slotBytesRecorded just noticed that recording must be interrupted
    // to split the file. The nth filename will follow the date/time
    // name of the first split but with a suffix.
    void splitContinueRecording();
    ControlProxy* m_recReady;
    ControlObject* m_recReadyCO;
    ControlPushButton* m_pToggleRecording;

    quint64 getFileSplitSize();
    int getFileSplitSeconds();

    UserSettingsPointer m_pConfig;
    QString m_recordingDir;
    // the base file
    QString m_recording_base_file;
    // filename without path
    QString m_recordingFile;
    // Absolute file
    QString m_recordingLocation;

    bool m_bRecording;
    // will be a very large number
    quint64 m_iNumberOfBytesRecorded;
    quint64 m_iNumberOfBytesRecordedSplit;
    quint64 m_split_size;
    long m_split_time;
    int m_iNumberSplits;
    long m_secondsRecorded;
    long m_secondsRecordedSplit;
    QString getRecordedDurationStr(quint64 duration);
};

#endif // RECORDINGMANAGER_H
