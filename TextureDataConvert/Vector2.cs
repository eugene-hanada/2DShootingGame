using System;
using System.Buffers.Binary;


namespace TextureDataConvert
{
	internal class Vector2
	{
		public float x;
		public float y;
		public Vector2(float x, float y)
		{
			this.x = x; 
			this.y = y;
		}

		public Vector2(Vector2 vector2)
		{
			this.x = vector2.x;
			this.y = vector2.y;
		}

		void Write(BinaryWriter bw)
		{
			bw.Write(x);
			bw.Write(y);
		}

	}
}
