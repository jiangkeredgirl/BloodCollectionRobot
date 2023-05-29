#pragma once

#include <string>
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <chrono>
#include <sstream>
#include <string>
#include <chrono>
#include <cinttypes>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;
using namespace chrono;



inline time_t GetNowDateTimeStamp()
{
    std::time_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return timestamp; //毫秒时间
}

inline time_t GetDateTimeStamp(const string& timestr)  ///< h:%d:m:%d:s:%d:ms:%d
{
    tm tm_;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, millisecond = 0;
    sscanf(timestr.c_str(), "%d-%d-%d %d.%d.%d.%d", &year, &month, &day, &hour, &minute, &second, &millisecond);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_) * 1000 + millisecond; //已经减了8个时区
    return t_; //毫秒时间
}

inline time_t GetDateTimeStamp(const string& timeformat, const string& timestr)  ///< h:%d:m:%d:s:%d:ms:%d
{
    tm tm_;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, millisecond = 0;
    sscanf(timestr.c_str(), timeformat.c_str(), &year, &month, &day, &hour, &minute, &second, &millisecond);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_) * 1000 + millisecond; //已经减了8个时区
    return t_; //毫秒时间
}

inline string GetDateTimeString(std::time_t timestamp)
{
    auto const millisecs = timestamp % 1000;
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(timestamp /= 1000)), "%Y-%m-%d %H.%M.%S") << "." << millisecs;
    return ss.str(); //毫秒时间
}

inline string GetDateString(std::time_t timestamp)
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(timestamp /= 1000)), "%Y-%m-%d");
    return ss.str(); //毫秒时间
}

inline string GetTimeString(std::time_t timestamp)
{
    auto const millisecs = timestamp % 1000;
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(timestamp /= 1000)), "%H.%M.%S") << "." << millisecs;
    return ss.str(); //毫秒时间
}


///////////////////////////////////////////////////////

inline time_t GetNowDateTimeStampMicro()
{
    std::time_t timestamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return timestamp; //微秒时间
}

inline time_t GetDateTimeStampMicro(const string& timestr)  ///< h:%d:m:%d:s:%d:ms:%d
{
    tm tm_;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, millisecond = 0, microsecond = 0;
    sscanf(timestr.c_str(), "%d-%d-%d %d.%d.%d.%d.%d", &year, &month, &day, &hour, &minute, &second, &millisecond, &microsecond);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_) * 1000000 + millisecond * 1000 + microsecond; //已经减了8个时区
    return t_; //微秒时间
}

inline time_t GetDateTimeStampMicro(const string& timeformat, const string& timestr)  ///< h:%d:m:%d:s:%d:ms:%d
{
    tm tm_;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, millisecond = 0, microsecond = 0;
    sscanf(timestr.c_str(), timeformat.c_str(), &year, &month, &day, &hour, &minute, &second, &millisecond, &microsecond);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_) * 1000000 + millisecond * 1000 + microsecond; //已经减了8个时区
    return t_; //微秒时间
}

inline string GetDateTimeStringMicro(std::time_t timestamp)
{
    auto const millisecs = (timestamp % 1000000) / 1000;
    auto const microsecs = timestamp % 1000;
    std::stringstream ss;
    ss << std::put_time(std::localtime(&(timestamp /= 1000)), "%Y-%m-%d %H.%M.%S") << "." << millisecs << "." << microsecs;
    return ss.str(); //微秒时间
}


///=========================================

inline int64_t GetThreadId(const std::thread* thread = nullptr)
{
    int64_t thread_id = 0;
    if(thread == nullptr)
    {
        stringstream ss;
        ss << std::this_thread::get_id();
        thread_id =  stoll(ss.str());
    }
    else
    {
        stringstream ss;
        ss << thread->get_id();
        thread_id =  stol(ss.str());
    }
    return thread_id;
}
#if 0
inline int GetThreadPolicy(int& policy, int& priority, int64_t thread_id = 0)
{
    int error_code = 0;
    if(thread_id == 0)
    {
        stringstream ss;
        ss << std::this_thread::get_id();
        thread_id =  stoll(ss.str());
    }
    printf("GetThreadPolicy  thread_id = %lld\n", (long long)thread_id);

    int _policy = 0;
    sched_param _param;
    _param.__sched_priority = 0;
    error_code = pthread_getschedparam(thread_id, &_policy, &_param);
    if(error_code == 0)
    {
        policy = _policy;
        switch(policy)
        {
        case SCHED_OTHER:
        {
            printf("get policy = SCHED_OTHER\n");
            break;
        }
        case SCHED_FIFO:
        {
            printf("get policy = SCHED_FIFO\n");
            priority = _param.__sched_priority;
            printf("get priority = %d\n", priority);
            int priority_min = sched_get_priority_min(policy);
            printf("get priority_min = %d\n",priority_min);
            int priority_max = sched_get_priority_max(policy);
            printf("get priority_max = %d\n",priority_max);
            break;
        }
        case SCHED_RR:
        {
            printf("get policy = SCHED_RR\n");
            priority = _param.__sched_priority;
            printf("get priority = %d\n", priority);
            int priority_min = sched_get_priority_min(policy);
            printf("get priority_min = %d\n",priority_min);
            int priority_max = sched_get_priority_max(policy);
            printf("get priority_max = %d\n",priority_max);
            break;
        }
        default:
            printf("get policy = %d UNKNOWN\n", policy);
            break;
        }
    }

    return error_code;
}


inline int SetThreadPolicy(int policy, int priority, int64_t thread_id = 0)
{
    int error_code = 0;
    if(thread_id == 0)
    {
        stringstream ss;
        ss << std::this_thread::get_id();
        thread_id =  stoll(ss.str());
    }
    printf("SetThreadPolicy  thread_id = %lld\n", (long long)thread_id);

    sched_param _param;
    _param.__sched_priority = priority;
    error_code = pthread_setschedparam(thread_id, policy, &_param);
    if(error_code == 0)
    {
        switch(policy)
        {
        case SCHED_OTHER:
        {
            printf("set policy = SCHED_OTHER\n");
            break;
        }
        case SCHED_FIFO:
        {
            printf("set policy = SCHED_FIFO\n");
            printf("set priority = %d\n", priority);
            int priority_min = sched_get_priority_min(policy);
            printf("set priority_min = %d\n",priority_min);
            int priority_max = sched_get_priority_max(policy);
            printf("set priority_max = %d\n",priority_max);
            break;
        }
        case SCHED_RR:
        {
            printf("set policy = SCHED_RR\n");
            printf("set priority = %d\n", priority);
            int priority_min = sched_get_priority_min(policy);
            printf("set priority_min = %d\n",priority_min);
            int priority_max = sched_get_priority_max(policy);
            printf("set priority_max = %d\n",priority_max);
            break;
        }
        default:
            printf("set policy = %d UNKNOWN\n", policy);
            break;
        }
    }

    return error_code;
}
#endif
///=========================================

#if 1
inline int CreateDir(const string& path)
{
    int error_code = 0;
    if (access(path.c_str(), 0) == -1)
    {
        string::size_type pos = path.find_last_of("\\/");
        if (pos != string::npos)
        {
            string base_path = path.substr(0, pos);
            CreateDir(base_path);
        }
        if (access(path.c_str(), 0) == -1)
        {
            error_code = mkdir(path.c_str());
        }
    }
#if 0
    if (error_code == 0)
    {
        std::cout << "[INFO]:Create directory " << path.c_str() << "   succeed\n";
    }
    else
    {
        std::cout << "[ERROR]:Create directory " << path.c_str() << "  failed,please configure your PC setting\n";
    }
#endif
    return error_code;
}

inline int DeleteDir(const string& path)
{
    char cmd[1024] = {0};
    sprintf(cmd, "rm -rf %s", path.c_str());
    system(cmd);
    return 0;
}
#endif
//inline int DeleteDir(const string& path)
//{
//        int error_code = -1;
//        if (access(path.c_str(), 0) == 0)
//        {
//                string filespec = path + "\\*.*";
//                struct __finddata64_t fileinfo;
//                intptr_t file = _findfirst64(filespec.c_str(), &fileinfo);
//                if (file != -1)
//                {
//                        while (_findnext64(file, &fileinfo) == 0)
//                        {
//                                string sub_file = path + "\\" + fileinfo.name;
//                                if (fileinfo.attrib == _A_SUBDIR)
//                                {
//                                        if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//                                        {
//                                                DeleteDir(sub_file);
//                                        }
//                                }
//                                else
//                                {
//                                        remove(sub_file.c_str());
//                                }
//                        }
//                        _findclose(file);
//                }
//                error_code = _rmdir(path.c_str());
//        }
//        return error_code;
//}
#if 0
inline bool IsDirectory(const char *pszName)
{
    struct stat S_stat;

    //取得文件状态
    if (lstat(pszName, &S_stat) < 0)
    {
        return false;
    }

    if (S_ISDIR(S_stat.st_mode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif