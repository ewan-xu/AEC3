cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

set (CMAKE_CXX_STANDARD 14)

#set(CMAKE_BUILD_TYPE "Release")

project(AEC3 C CXX)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
    set(CMAKE_CXX_FLAGS "-stdlib=libc++")
endif()

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE rtc_base)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if (APPLE)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    endif()
elseif(WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    endif()
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /W1
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W3
            >
            /sdl;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    AEC3
    base
)

if (WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "winmm"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "winmm"
        )
    endif()
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

set(PROJECT_NAME AEC3)

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
    "audio_processing/aec3/false_comfort_noise_generator.cc"
    "audio_processing/aec3/false_comfort_noise_generator.h"
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
    "audio_processing/aec3/scaled_comfort_noise_generator.cc"
    "audio_processing/aec3/scaled_comfort_noise_generator.h"
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
    "audio_processing/resampler/sinc_resampler_sse.cc"
)
source_group("audio_processing\\resampler" FILES ${audio_processing__resampler})

set(audio_processing__utility
    "audio_processing/utility/cascaded_biquad_filter.cc"
    "audio_processing/utility/cascaded_biquad_filter.h"
    "audio_processing/utility/ooura_fft.cc"
    "audio_processing/utility/ooura_fft.h"
    "audio_processing/utility/ooura_fft_mips.cc"
    "audio_processing/utility/ooura_fft_neon.cc"
    "audio_processing/utility/ooura_fft_sse2.cc"
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

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AEC3)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing/aec3"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing;"
        "${CMAKE_CURRENT_SOURCE_DIR}/audio_processing/aec3"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if (APPLE)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    endif()
elseif(WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    endif()
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /MP;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm;
                /Od;
                /W1
            >
            $<$<CONFIG:Release>:
                /MP;
                /O2;
                /Oi;
                /Gy;
                /W3
            >
            /sdl;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "rtc_base"
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/libs/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

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

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE rtc_base)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if (APPLE)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    endif()
elseif(WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    endif()
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /W1
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W3
            >
            /sdl;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "jsoncpp;"
            "winmm"
        ">"
    )
endif()

if (APPLE)
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "-framework CoreFoundation"
            ${ADDITIONAL_LIBRARY_DEPENDENCIES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/libs/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

set(PROJECT_NAME demo)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "demo/demo.cc"
    "demo/wavreader.c"
    "demo/wavreader.h"
    "demo/wavwriter.c"
    "demo/wavwriter.h"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE rtc_base)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/$<CONFIG>_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/abseil;"
        "${CMAKE_CURRENT_SOURCE_DIR}/base/jsoncpp/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if (APPLE)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
                "$<$<CONFIG:Debug>:"
                "_DEBUG"
                ">"
                "$<$<CONFIG:Release>:"
                "DEBUG"
                ">"
                "WEBRTC_MAC;"
                "WEBRTC_POSIX;"
                "_WINDOWS;"
                "NOMINMAX;"
                "_CRT_SECURE_NO_WARNINGS;"
                "_SCL_SECURE_NO_WARNINGS;"
                "WIN32_LEAN_AND_MEAN;"
                "_MBCS"
                )
    endif()
elseif(WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_definitions(${PROJECT_NAME} PRIVATE
            "$<$<CONFIG:Debug>:"
                "_DEBUG"
            ">"
            "$<$<CONFIG:Release>:"
                "DEBUG"
            ">"
            "WEBRTC_WIN;"
            "_WINDOWS;"
            "NOMINMAX;"
            "_CRT_SECURE_NO_WARNINGS;"
            "_SCL_SECURE_NO_WARNINGS;"
            "WIN32_LEAN_AND_MEAN;"
            "_MBCS"
        )
    endif()
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /W1
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W3
            >
            /sdl;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4005;
            /wd4068;
            /wd4180;
            /wd4244;
            /wd4267;
            /wd4503;
            /wd4800;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    AEC3
    api
    base
)

if (WIN32)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "winmm"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "winmm"
        )
    endif()
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${OUTPUT_DIRECTORY}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${OUTPUT_DIRECTORY}"
    )
endif()

