// Copyright Ingo Proff 2017.
// https://github.com/CrikeeIP/Stopwatch
// Distributed under the MIT Software License (X11 license).
// (See accompanying file LICENSE)

#pragma once

#include <cassert>
#include <chrono>


namespace stopwatch{

class Stopwatch{
public:
   Stopwatch( bool auto_start = false): start_time() {
      if( auto_start ){
         start();
      }
   }

   void start(){
      start_time = std::chrono::high_resolution_clock::now();
   }

   enum TimeFormat{ NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS };

   template<TimeFormat fmt = TimeFormat::MILLISECONDS>
   std::uint64_t elapsed(){
      if( start_time == std::chrono::time_point<std::chrono::high_resolution_clock>() ){
         //start_time has not been initialized using start()
         assert(false);
         return 0;
      }

      const auto end_time = std::chrono::high_resolution_clock::now();
      const auto duration = end_time - start_time;
      const std::uint64_t ns_count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

      switch(fmt){
      case TimeFormat::NANOSECONDS:
      {
         return ns_count;
      }
      case TimeFormat::MICROSECONDS:
      {
         std::uint64_t up = ((ns_count/100)%10 >= 5) ? 1 : 0;
         const auto mus_count = (ns_count /1000) + up;
         return mus_count;
      }
      case TimeFormat::MILLISECONDS:
      {
         std::uint64_t up = ((ns_count/100000)%10 >= 5) ? 1 : 0;
         const auto ms_count = (ns_count /1000000) + up;
         return ms_count;
      }
       case TimeFormat::SECONDS:
      {
         std::uint64_t up = ((ns_count/100000000)%10 >= 5) ? 1 : 0;
         const auto s_count = (ns_count /1000000000) + up;
         return s_count;
      }
      default:
         assert(false);
         return 1;
      }
   }

private:
   std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

constexpr Stopwatch::TimeFormat ns = Stopwatch::TimeFormat::NANOSECONDS;
constexpr Stopwatch::TimeFormat mus = Stopwatch::TimeFormat::MICROSECONDS;
constexpr Stopwatch::TimeFormat ms = Stopwatch::TimeFormat::MILLISECONDS;
constexpr Stopwatch::TimeFormat s = Stopwatch::TimeFormat::SECONDS;

constexpr Stopwatch::TimeFormat nanoseconds = Stopwatch::TimeFormat::NANOSECONDS;
constexpr Stopwatch::TimeFormat microseconds = Stopwatch::TimeFormat::MICROSECONDS;
constexpr Stopwatch::TimeFormat milliseconds = Stopwatch::TimeFormat::MILLISECONDS;
constexpr Stopwatch::TimeFormat seconds = Stopwatch::TimeFormat::SECONDS;

} //namespace stopwatch
