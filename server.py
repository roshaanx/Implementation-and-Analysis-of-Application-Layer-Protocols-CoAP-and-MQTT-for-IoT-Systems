import asyncio
from aiocoap import resource, Context, Message, CHANGED

class TestResource(resource.Resource):
    async def render_put(self, request):
        data = request.payload.decode()
        print("Received from ESP:", data)

        # Send SAME data back (important for assignment)
        return Message(code=CHANGED, payload=request.payload)

async def main():
    root = resource.Site()
    root.add_resource(['test'], TestResource())

    await Context.create_server_context(root)

    print("CoAP server running on port 5683...")
    await asyncio.get_running_loop().create_future()

if __name__ == "__main__":
    asyncio.run(main())