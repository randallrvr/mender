#include <mtlpp/mtlpp.hpp>

#include "window.hpp"
#include "MetalApp.h"

#include <vector>
#include <string>

mtlpp::Device              g_device;
mtlpp::CommandQueue        g_commandQueue;
mtlpp::Buffer              g_vertexBuffer;
mtlpp::RenderPipelineState g_renderPipelineState;

void Render(const Window& win)
{
	// Get Command Buffer from Command Queue
	mtlpp::CommandBuffer commandBuffer = g_commandQueue.CommandBuffer();

	// Get Render Pass Description from window
    mtlpp::RenderPassDescriptor renderPassDesc = win.GetRenderPassDescriptor();

	if(renderPassDesc)
    {
		// Get Render Command Encoder
        mtlpp::RenderCommandEncoder renderCommandEncoder = commandBuffer.RenderCommandEncoder(renderPassDesc);

		// Set Render Pipeline State / Vertex Buffers / Draw Type
		renderCommandEncoder.SetRenderPipelineState(g_renderPipelineState);
        renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
        renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
        renderCommandEncoder.EndEncoding();

		// Draw
        commandBuffer.Present(win.GetDrawable());
    }

    commandBuffer.Commit();
    commandBuffer.WaitUntilCompleted();
}

int main(int argc, char *argv[])
{
/*
    const char shadersSrc[] = R"(
        #include <metal_stdlib>
        using namespace metal;

        vertex float4 vertFunc(
            const device packed_float3* vertexArray [[buffer(0)]],
            unsigned int vID[[vertex_id]])
        {
            return float4(vertexArray[vID], 1.0);
        }

        fragment half4 fragFunc()
        {
            return half4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    const float vertexData[] =
    {
         0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };

	// Create Metal device
    g_device = mtlpp::Device::CreateSystemDefaultDevice();

	// Create command queue
    g_commandQueue = g_device.NewCommandQueue();

	// Metal Library
    mtlpp::Library library = g_device.NewLibrary(shadersSrc, mtlpp::CompileOptions(), nullptr);

	// Metal Shader Functions
    mtlpp::Function vertFunc = library.NewFunction("vertFunc");
    mtlpp::Function fragFunc = library.NewFunction("fragFunc");

	// Create Vertex Buffer
    g_vertexBuffer = g_device.NewBuffer(vertexData, sizeof(vertexData), mtlpp::ResourceOptions::CpuCacheModeDefaultCache);

	// Render Pipeline Description
    mtlpp::RenderPipelineDescriptor renderPipelineDesc;

	// Set Shader Funcions and attachments
    renderPipelineDesc.SetVertexFunction(vertFunc);
    renderPipelineDesc.SetFragmentFunction(fragFunc);
    renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(mtlpp::PixelFormat::BGRA8Unorm);

    // Get Render Pipeline state
	g_renderPipelineState = g_device.NewRenderPipelineState(renderPipelineDesc, nullptr);

	// Create Window and pass render function to it
    Window win(g_device, &Render, 640, 480);

	// Run
    Window::Run();
*/

	std::vector<std::string> args;
	for(int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	MetalApp metalApp("Metal App", 1280, 720, args);
//	metalApp.run();

	return 0;

    return 0;
}

