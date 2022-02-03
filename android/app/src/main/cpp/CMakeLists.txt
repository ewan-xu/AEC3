# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

set (CMAKE_CXX_STANDARD 14)

# Declares and names the project.

project("aec3")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        aec3-shared

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        PinPointAEC3AndroidAPI.h
        PinPointAEC3AndroidAPI.cpp
        native-lib.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        aec3-shared
        api
        audioprocessing
        base
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

################################################################################
# Sub-projects
################################################################################

set(PROJECT_NAME api)

################################################################################
# Source groups
################################################################################
set(api
        "api/echo_canceller3_config.cc"
        "api/echo_canceller3_config.h"
        "api/echo_canceller3_config_json.cc"
        "api/echo_canceller3_config_json.h"
        "api/echo_canceller3_factory.cc"
        "api/echo_canceller3_factory.h"
        "api/echo_control.h"
        )
source_group("api" FILES ${api})

set(ALL_FILES
        ${api}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

set(ROOT_NAMESPACE rtc_base)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpu_features-0.6.0/ndk_compat"
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "DEBUG"
        ">"
        "WEBRTC_POSIX;"
        "WEBRTC_LINUX;"
        "WEBRTC_ANDROID"
        )

target_link_libraries(${PROJECT_NAME} PUBLIC
        base
        )

set(PROJECT_NAME audioprocessing)

################################################################################
# Source groups
################################################################################
set(audio_processing
        "audio_processing/audio_buffer.cc"
        "audio_processing/audio_buffer.h"
        "audio_processing/audio_frame.cc"
        "audio_processing/audio_frame.h"
        "audio_processing/channel_buffer.cc"
        "audio_processing/channel_buffer.h"
        "audio_processing/channel_layout.cc"
        "audio_processing/channel_layout.h"
        "audio_processing/high_pass_filter.cc"
        "audio_processing/high_pass_filter.h"
        "audio_processing/sparse_fir_filter.cc"
        "audio_processing/sparse_fir_filter.h"
        "audio_processing/splitting_filter.cc"
        "audio_processing/splitting_filter.h"
        "audio_processing/splitting_filter_c.c"
        "audio_processing/three_band_filter_bank.cc"
        "audio_processing/three_band_filter_bank.h"
        )
source_group("audio_processing" FILES ${audio_processing})

set(audio_processing__aec3
        "audio_processing/aec3/adaptive_fir_filter.cc"
        "audio_processing/aec3/adaptive_fir_filter.h"
        "audio_processing/aec3/adaptive_fir_filter_erl.cc"
        "audio_processing/aec3/adaptive_fir_filter_erl.h"
        "audio_processing/aec3/aec3_common.cc"
        "audio_processing/aec3/aec3_common.h"
        "audio_processing/aec3/aec3_fft.cc"
        "audio_processing/aec3/aec3_fft.h"
        "audio_processing/aec3/aec_state.cc"
        "audio_processing/aec3/aec_state.h"
        "audio_processing/aec3/alignment_mixer.cc"
        "audio_processing/aec3/alignment_mixer.h"
        "audio_processing/aec3/api_call_jitter_metrics.cc"
        "audio_processing/aec3/api_call_jitter_metrics.h"
        "audio_processing/aec3/block_buffer.cc"
        "audio_processing/aec3/block_buffer.h"
        "audio_processing/aec3/block_delay_buffer.cc"
        "audio_processing/aec3/block_delay_buffer.h"
        "audio_processing/aec3/block_framer.cc"
        "audio_processing/aec3/block_framer.h"
        "audio_processing/aec3/block_processor.cc"
        "audio_processing/aec3/block_processor.h"
        "audio_processing/aec3/block_processor_metrics.cc"
        "audio_processing/aec3/block_processor_metrics.h"
        "audio_processing/aec3/clockdrift_detector.cc"
        "audio_processing/aec3/clockdrift_detector.h"
        "audio_processing/aec3/comfort_noise_generator.cc"
        "audio_processing/aec3/comfort_noise_generator.h"
        "audio_processing/aec3/decimator.cc"
        "audio_processing/aec3/decimator.h"
        "audio_processing/aec3/delay_estimate.h"
        "audio_processing/aec3/dominant_nearend_detector.cc"
        "audio_processing/aec3/dominant_nearend_detector.h"
        "audio_processing/aec3/downsampled_render_buffer.cc"
        "audio_processing/aec3/downsampled_render_buffer.h"
        "audio_processing/aec3/echo_audibility.cc"
        "audio_processing/aec3/echo_audibility.h"
        "audio_processing/aec3/echo_canceller3.cc"
        "audio_processing/aec3/echo_canceller3.h"
        "audio_processing/aec3/echo_path_delay_estimator.cc"
        "audio_processing/aec3/echo_path_delay_estimator.h"
        "audio_processing/aec3/echo_path_variability.cc"
        "audio_processing/aec3/echo_path_variability.h"
        "audio_processing/aec3/echo_remover.cc"
        "audio_processing/aec3/echo_remover.h"
        "audio_processing/aec3/echo_remover_metrics.cc"
        "audio_processing/aec3/echo_remover_metrics.h"
        "audio_processing/aec3/erl_estimator.cc"
        "audio_processing/aec3/erl_estimator.h"
        "audio_processing/aec3/erle_estimator.cc"
        "audio_processing/aec3/erle_estimator.h"
        "audio_processing/aec3/fft_buffer.cc"
        "audio_processing/aec3/fft_buffer.h"
        "audio_processing/aec3/fft_data.h"
        "audio_processing/aec3/filter_analyzer.cc"
        "audio_processing/aec3/filter_analyzer.h"
        "audio_processing/aec3/frame_blocker.cc"
        "audio_processing/aec3/frame_blocker.h"
        "audio_processing/aec3/fullband_erle_estimator.cc"
        "audio_processing/aec3/fullband_erle_estimator.h"
        "audio_processing/aec3/main_filter_update_gain.cc"
        "audio_processing/aec3/main_filter_update_gain.h"
        "audio_processing/aec3/matched_filter.cc"
        "audio_processing/aec3/matched_filter.h"
        "audio_processing/aec3/matched_filter_lag_aggregator.cc"
        "audio_processing/aec3/matched_filter_lag_aggregator.h"
        "audio_processing/aec3/moving_average.cc"
        "audio_processing/aec3/moving_average.h"
        "audio_processing/aec3/nearend_detector.h"
        "audio_processing/aec3/render_buffer.cc"
        "audio_processing/aec3/render_buffer.h"
        "audio_processing/aec3/render_delay_buffer.cc"
        "audio_processing/aec3/render_delay_buffer.h"
        "audio_processing/aec3/render_delay_controller.cc"
        "audio_processing/aec3/render_delay_controller.h"
        "audio_processing/aec3/render_delay_controller_metrics.cc"
        "audio_processing/aec3/render_delay_controller_metrics.h"
        "audio_processing/aec3/render_signal_analyzer.cc"
        "audio_processing/aec3/render_signal_analyzer.h"
        "audio_processing/aec3/residual_echo_estimator.cc"
        "audio_processing/aec3/residual_echo_estimator.h"
        "audio_processing/aec3/reverb_decay_estimator.cc"
        "audio_processing/aec3/reverb_decay_estimator.h"
        "audio_processing/aec3/reverb_frequency_response.cc"
        "audio_processing/aec3/reverb_frequency_response.h"
        "audio_processing/aec3/reverb_model.cc"
        "audio_processing/aec3/reverb_model.h"
        "audio_processing/aec3/reverb_model_estimator.cc"
        "audio_processing/aec3/reverb_model_estimator.h"
        "audio_processing/aec3/shadow_filter_update_gain.cc"
        "audio_processing/aec3/shadow_filter_update_gain.h"
        "audio_processing/aec3/signal_dependent_erle_estimator.cc"
        "audio_processing/aec3/signal_dependent_erle_estimator.h"
        "audio_processing/aec3/spectrum_buffer.cc"
        "audio_processing/aec3/spectrum_buffer.h"
        "audio_processing/aec3/stationarity_estimator.cc"
        "audio_processing/aec3/stationarity_estimator.h"
        "audio_processing/aec3/subband_erle_estimator.cc"
        "audio_processing/aec3/subband_erle_estimator.h"
        "audio_processing/aec3/subband_nearend_detector.cc"
        "audio_processing/aec3/subband_nearend_detector.h"
        "audio_processing/aec3/subtractor.cc"
        "audio_processing/aec3/subtractor.h"
        "audio_processing/aec3/subtractor_output.cc"
        "audio_processing/aec3/subtractor_output.h"
        "audio_processing/aec3/subtractor_output_analyzer.cc"
        "audio_processing/aec3/subtractor_output_analyzer.h"
        "audio_processing/aec3/suppression_filter.cc"
        "audio_processing/aec3/suppression_filter.h"
        "audio_processing/aec3/suppression_gain.cc"
        "audio_processing/aec3/suppression_gain.h"
        "audio_processing/aec3/vector_math.h"
        )
source_group("audio_processing\\aec3" FILES ${audio_processing__aec3})

set(audio_processing__include
        "audio_processing/include/audio_processing.h"
        "audio_processing/include/audio_util.h"
        )
source_group("audio_processing\\include" FILES ${audio_processing__include})

set(audio_processing__logging
        "audio_processing/logging/apm_data_dumper.cc"
        "audio_processing/logging/apm_data_dumper.h"
        "audio_processing/logging/wav_file.cc"
        "audio_processing/logging/wav_file.h"
        "audio_processing/logging/wav_header.cc"
        "audio_processing/logging/wav_header.h"
        )
source_group("audio_processing\\logging" FILES ${audio_processing__logging})

set(audio_processing__resampler
        "audio_processing/resampler/push_sinc_resampler.cc"
        "audio_processing/resampler/push_sinc_resampler.h"
        "audio_processing/resampler/sinc_resampler.cc"
        "audio_processing/resampler/sinc_resampler.h"
        "audio_processing/resampler/sinc_resampler_neon.cc"
        #"audio_processing/resampler/sinc_resampler_sse.cc"
        )
source_group("audio_processing\\resampler" FILES ${audio_processing__resampler})

set(audio_processing__utility
        "audio_processing/utility/cascaded_biquad_filter.cc"
        "audio_processing/utility/cascaded_biquad_filter.h"
        "audio_processing/utility/ooura_fft.cc"
        "audio_processing/utility/ooura_fft.h"
        "audio_processing/utility/ooura_fft_mips.cc"
        "audio_processing/utility/ooura_fft_neon.cc"
        #"audio_processing/utility/ooura_fft_sse2.cc"
        "audio_processing/utility/ooura_fft_tables_common.h"
        "audio_processing/utility/ooura_fft_tables_neon_sse2.h"
        )
source_group("audio_processing\\utility" FILES ${audio_processing__utility})

set(ALL_FILES
        ${audio_processing}
        ${audio_processing__aec3}
        ${audio_processing__include}
        ${audio_processing__logging}
        ${audio_processing__resampler}
        ${audio_processing__utility}
        )

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

set(ROOT_NAMESPACE aec3)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing/aec3;"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpu_features-0.6.0/ndk_compat"
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "DEBUG"
        ">"
        "WEBRTC_POSIX;"
        "WEBRTC_LINUX;"
        "WEBRTC_ANDROID"
        )

#set(ADDITIONAL_LIBRARY_DEPENDENCIES
#        "$<$<CONFIG:Debug>:"
#        "rtc_base"
#        ">"
#        )

#target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

set(PROJECT_NAME base)

################################################################################
# Source groups
################################################################################
set(absl__bad_optional_access
        "base/abseil/absl/types/bad_optional_access.cc"
        "base/abseil/absl/types/bad_optional_access.h"
        )
source_group("absl\\bad_optional_access" FILES ${absl__bad_optional_access})

set(absl__strings__Header_Files
        "base/abseil/absl/strings/ascii.h"
        "base/abseil/absl/strings/charconv.h"
        "base/abseil/absl/strings/escaping.h"
        "base/abseil/absl/strings/internal/charconv_bigint.h"
        "base/abseil/absl/strings/internal/charconv_parse.h"
        "base/abseil/absl/strings/internal/memutil.h"
        "base/abseil/absl/strings/internal/stl_type_traits.h"
        "base/abseil/absl/strings/internal/str_join_internal.h"
        "base/abseil/absl/strings/internal/str_split_internal.h"
        "base/abseil/absl/strings/match.h"
        "base/abseil/absl/strings/numbers.h"
        "base/abseil/absl/strings/str_cat.h"
        "base/abseil/absl/strings/str_format.h"
        "base/abseil/absl/strings/str_join.h"
        "base/abseil/absl/strings/str_replace.h"
        "base/abseil/absl/strings/str_split.h"
        "base/abseil/absl/strings/string_view.h"
        "base/abseil/absl/strings/substitute.h"
        )
source_group("absl\\strings\\Header Files" FILES ${absl__strings__Header_Files})

set(absl__strings__Source_Files
        "base/abseil/absl/strings/ascii.cc"
        "base/abseil/absl/strings/charconv.cc"
        "base/abseil/absl/strings/escaping.cc"
        "base/abseil/absl/strings/internal/charconv_bigint.cc"
        "base/abseil/absl/strings/internal/charconv_parse.cc"
        "base/abseil/absl/strings/internal/memutil.cc"
        "base/abseil/absl/strings/match.cc"
        "base/abseil/absl/strings/numbers.cc"
        "base/abseil/absl/strings/str_cat.cc"
        "base/abseil/absl/strings/str_replace.cc"
        "base/abseil/absl/strings/str_split.cc"
        "base/abseil/absl/strings/string_view.cc"
        "base/abseil/absl/strings/substitute.cc"
        )
source_group("absl\\strings\\Source Files" FILES ${absl__strings__Source_Files})

set(absl__throw_delegate
        "base/abseil/absl/base/internal/throw_delegate.cc"
        "base/abseil/absl/base/internal/throw_delegate.h"
        )
source_group("absl\\throw_delegate" FILES ${absl__throw_delegate})

set(jsoncpp__Header_Files
        "base/jsoncpp/src/lib_json/json_batchallocator.h"
        "base/jsoncpp/src/lib_json/json_tool.h"
        "base/jsoncpp/src/lib_json/json_valueiterator.inl"
        )
source_group("jsoncpp\\Header Files" FILES ${jsoncpp__Header_Files})

set(jsoncpp__Public_API
        "base/jsoncpp/include/json/assertions.h"
        "base/jsoncpp/include/json/autolink.h"
        "base/jsoncpp/include/json/config.h"
        "base/jsoncpp/include/json/features.h"
        "base/jsoncpp/include/json/forwards.h"
        "base/jsoncpp/include/json/json.h"
        "base/jsoncpp/include/json/reader.h"
        "base/jsoncpp/include/json/value.h"
        "base/jsoncpp/include/json/version.h"
        "base/jsoncpp/include/json/writer.h"
        )
source_group("jsoncpp\\Public API" FILES ${jsoncpp__Public_API})

set(jsoncpp__Source_Files
        "base/jsoncpp/src/lib_json/json_reader.cpp"
        "base/jsoncpp/src/lib_json/json_value.cpp"
        "base/jsoncpp/src/lib_json/json_writer.cpp"
        )
source_group("jsoncpp\\Source Files" FILES ${jsoncpp__Source_Files})

set(rtc_base
        "base/rtc_base/array_view.h"
        "base/rtc_base/arraysize.h"
        "base/rtc_base/atomic_ops.h"
        "base/rtc_base/checks.cc"
        "base/rtc_base/checks.h"
        "base/rtc_base/constructor_magic.h"
        "base/rtc_base/critical_section.cc"
        "base/rtc_base/critical_section.h"
        "base/rtc_base/gtest_prod_util.h"
        "base/rtc_base/logging.cc"
        "base/rtc_base/logging.h"
        "base/rtc_base/platform_thread_types.cc"
        "base/rtc_base/platform_thread_types.h"
        "base/rtc_base/race_checker.cc"
        "base/rtc_base/race_checker.h"
        "base/rtc_base/sanitizer.h"
        "base/rtc_base/string_encode.cc"
        "base/rtc_base/string_encode.h"
        "base/rtc_base/string_to_number.cc"
        "base/rtc_base/string_to_number.h"
        "base/rtc_base/string_utils.cc"
        "base/rtc_base/string_utils.h"
        "base/rtc_base/swap_queue.h"
        "base/rtc_base/thread_annotations.h"
        "base/rtc_base/time_utils.cc"
        "base/rtc_base/time_utils.h"
        "base/rtc_base/type_traits.h"
        )
source_group("rtc_base" FILES ${rtc_base})

set(rtc_base__memory
        "base/rtc_base/memory/aligned_malloc.cc"
        "base/rtc_base/memory/aligned_malloc.h"
        )
source_group("rtc_base\\memory" FILES ${rtc_base__memory})

set(rtc_base__numerics
        "base/rtc_base/numerics/safe_compare.h"
        "base/rtc_base/numerics/safe_conversions.h"
        "base/rtc_base/numerics/safe_conversions_impl.h"
        "base/rtc_base/numerics/safe_minmax.h"
        )
source_group("rtc_base\\numerics" FILES ${rtc_base__numerics})

set(rtc_base__strings
        "base/rtc_base/strings/json.cc"
        "base/rtc_base/strings/json.h"
        "base/rtc_base/strings/string_builder.cc"
        "base/rtc_base/strings/string_builder.h"
        )
source_group("rtc_base\\strings" FILES ${rtc_base__strings})

set(rtc_base__system
        "base/rtc_base/system/arch.h"
        "base/rtc_base/system/file_wrapper.cc"
        "base/rtc_base/system/file_wrapper.h"
        "base/rtc_base/system/inline.h"
        "base/rtc_base/system/rtc_export.h"
        "base/rtc_base/system/unused.h"
        )
source_group("rtc_base\\system" FILES ${rtc_base__system})

set(system_wrappers
        "base/system_wrappers/include/cpu_features_wrapper.h"
        "base/system_wrappers/include/field_trial.h"
        "base/system_wrappers/include/metrics.h"
        "base/system_wrappers/source/cpu_features.cc"
        "base/system_wrappers/source/cpu_features_android.c"
        "base/system_wrappers/source/cpu_features_linux.c"
        "base/system_wrappers/source/field_trial.cc"
        "base/system_wrappers/source/metrics.cc"
        )
source_group("system_wrappers" FILES ${system_wrappers})

set(ALL_FILES
        ${absl__bad_optional_access}
        ${absl__strings__Header_Files}
        ${absl__strings__Source_Files}
        ${absl__throw_delegate}
        ${jsoncpp__Header_Files}
        ${jsoncpp__Public_API}
        ${jsoncpp__Source_Files}
        ${rtc_base}
        ${rtc_base__memory}
        ${rtc_base__numerics}
        ${rtc_base__strings}
        ${rtc_base__system}
        ${system_wrappers}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

set(ROOT_NAMESPACE rtc_base)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpu_features-0.6.0/ndk_compat"
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "DEBUG"
        ">"
        "WEBRTC_POSIX;"
        "WEBRTC_LINUX;"
        "WEBRTC_ANDROID"
        )

################################################################################
# Dependencies
################################################################################
#set(ADDITIONAL_LIBRARY_DEPENDENCIES
#        "$<$<CONFIG:Debug>:"
#        "jsoncpp;"
#        ">"
#        )

#target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")